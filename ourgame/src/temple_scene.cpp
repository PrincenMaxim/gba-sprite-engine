//
// Created by Gebruiker on 23/12/2020.
//

#include "temple_scene.h"

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <memory>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "backgrounds/temple_input.h"
#include "sprites/pink_guy_sprites.h"
#include "sprites/owlet_sprites.h"
#include "sprites/dude_sprites.h"
#include "death_scene.h"
#include "floatingIslands_scene.h"

std::vector<Sprite *> temple_scene::sprites(){
    return{player.getSprite()};
};

std::vector<Background *> temple_scene::backgrounds(){
    return{
            bg_statics.get(),
            bg_dynamics.get(),
            bg_3_filler.get()
    };
}

void temple_scene::load() {
    engine.get()->enableText();


    switch (skin_choice) {
        case 0 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
                    new ForegroundPaletteManager(pink_guy_sharedPal, sizeof(pink_guy_sharedPal)));
            break;
        case 1 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
                    new ForegroundPaletteManager(owlet_sharedPal, sizeof(owlet_sharedPal)));
            break;
        case 2 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
                    new ForegroundPaletteManager(dude_sharedPal, sizeof(dude_sharedPal)));
            break;
    }


    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(temple_sharedPal, sizeof(temple_sharedPal)));

    bg_statics = std::unique_ptr<Background>(
            new Background(1, temple_staticsTiles, sizeof(temple_staticsTiles),
                           temple_map, sizeof(temple_map), 18, 1, MAPLAYOUT_32X64));
    bg_dynamics = std::unique_ptr<Background>(
            new Background(2, temple_cloudsTiles, sizeof(temple_cloudsTiles),
                           temple_clouds_map, sizeof(temple_clouds_map),
                           14, 2, MAPLAYOUT_32X32));
    bg_3_filler = std::unique_ptr<Background>(
            new Background(3, temple_cloudsTiles, sizeof(temple_cloudsTiles),
                           temple_clouds_map, sizeof(temple_clouds_map),
                           14, 3, MAPLAYOUT_32X32));
    //is hetzelfde als
    //bg_statics->useMapScreenBlock(18);
    //bg_dynamics->useMapScreenBlock(14);
    //bg_3_filler->useMapScreenBlock(14);

    player.setBuilder(builder, startY, skin_choice); //!!!!!!!!!!!!!!!hier nog skin_choice invullen!
}

void temple_scene::tick(u16 keys){
    TextStream::instance().clear();
    moveLeft = keys & KEY_LEFT;
    moveRight = keys & KEY_RIGHT;
    moveUp = keys & KEY_UP;
    moveDown = keys & KEY_DOWN;
    bPressed = keys & KEY_B;
    TextStream::instance().setText("x_tile: " + std::to_string(player.calcTileX()),1,1);
    TextStream::instance().setText("y_tile: " + std::to_string(player.calcTileY()),2,1);
    TextStream::instance().setText("jumpTimer: " + std::to_string(player.getJumpTimer()),3,1);
    TextStream::instance().setText("collision: " + std::to_string(player.collision(moveUp, moveDown, moveLeft, moveRight,
                                                                                   nullptr, collisionMap_temple, mapWidth)),4,1);
    //TextStream::instance().setFontColor(BLD_BG0);


    timer += 1;
    if (timer % 30 == 0) {
        scrollX++;
        //bg_dynamics.get()->scroll(scrollX, 0);
    }

    if(player.getPosX()%1==0 && player.getPosX()>40 && keys & KEY_RIGHT && scrollStatics < 270 &&
       player.collision(moveUp,moveDown,moveLeft,moveRight, nullptr, collisionMap_temple,mapWidth) == 0){
        if(bPressed) scrollStatics += 2;
        else scrollStatics += 1;
        bg_statics.get()->scroll(scrollStatics,0);

    }
    if(player.getPosX()%1==0 && player.getPosX()>40 && keys & KEY_LEFT && scrollStatics > 0 && player.getPosX() < 200 &&
       player.collision(moveUp,moveDown,moveLeft,moveRight, nullptr, collisionMap_temple,mapWidth) == 0){
        if(bPressed) scrollStatics -= 2;
        else scrollStatics -= 1;
        bg_statics.get()->scroll(scrollStatics,0);

    }

    player.calcJumpDirection(moveUp, moveLeft, moveRight);

    //running
    if(bPressed){
        player.move(moveUp, moveDown, moveLeft, moveRight, nullptr, this->collisionMap_temple, bPressed, mapWidth, scrollStatics);
    }
        //walking
    else {
        if (timer % 2 == 0) {
            player.move(moveUp, moveDown, moveLeft, moveRight, nullptr, this->collisionMap_temple, bPressed, mapWidth, scrollStatics);
        }
    }
    player.isIdle(moveUp, moveDown, moveLeft, moveRight);
    player.setGravity(nullptr, this->collisionMap_temple, mapWidth, scrollStatics);

    if(player.calcTileX()==62) {
        floatingIslands_scene* floatingIslandsScene = new floatingIslands_scene(engine,skin_choice);
        engine->setScene(floatingIslandsScene);
        bg_dynamics.get()->scroll(0,0);
        bg_statics.get()->scroll(0,0);
    }

    if(player.fellOfMap(nullptr, this->collisionMap_temple, mapWidth)) {
        death_scene *deathScene = new death_scene(engine, skin_choice);

        engine->transitionIntoScene(deathScene, new FadeOutScene(2));
        bg_dynamics.get()->scroll(0, 0);
        bg_statics.get()->scroll(0,0);

    }

}