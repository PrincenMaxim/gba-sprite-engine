//
// Created by Maxim on 15/12/2020.
//

#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "level1_scene.h"
#include "backgrounds/level1_input.h"
#include <memory>

#include "sprites/pink_guy_sprites.h"
#include "sprites/owlet_sprites.h"
#include "sprites/dude_sprites.h"
#include "death_scene.h"
#include "player.h"
#include "temple_scene.h"



std::vector<Sprite *> level1_scene::sprites(){
    return{player.getSprite()};
};

std::vector<Background *> level1_scene::backgrounds() {
    return {
            bg_statics.get(),
            bg_dynamics.get(),
            bg_3_filler.get(),
    };
}


void level1_scene::load(){
    engine.get()->enableText();

    switch(skin_choice){
        case 0 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(pink_guy_sharedPal, sizeof(pink_guy_sharedPal)));
            break;
        case 1 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(owlet_sharedPal, sizeof(owlet_sharedPal)));
            break;
        case 2 :
            foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(dude_sharedPal, sizeof(dude_sharedPal)));
            break;
    }


    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(sharedPal, sizeof(sharedPal)));

    bg_statics = std::unique_ptr<Background>(new Background(1, staticsTiles, sizeof(staticsTiles),
                                                            statics_map, sizeof(statics_map),
                                                            18, 1, MAPLAYOUT_32X32));
    bg_dynamics = std::unique_ptr<Background>(new Background(2, cloudsTiles, sizeof(cloudsTiles),
                                                             clouds_map, sizeof(clouds_map),
                                                             14, 2, MAPLAYOUT_32X32));
    bg_3_filler = std::unique_ptr<Background>(new Background(3, cloudsTiles, sizeof(cloudsTiles),
                                                             clouds_map, sizeof(clouds_map),
                                                             14, 3, MAPLAYOUT_32X32));
    //is hetzelfde als
    //bg_statics->useMapScreenBlock(18);
    //bg_dynamics->useMapScreenBlock(14);
    //bg_3_filler->useMapScreenBlock(14);

    player.setBuilder(builder,startY, skin_choice);


    };

void level1_scene::tick(u16 keys) {
    //Scroll voor dynamic background

    TextStream::instance().clear();
    TextStream::instance().setText("X: " + std::to_string(player.calcTileX()),1,1);
    TextStream::instance().setText("Y: " + std::to_string(player.calcTileY()),2,1);
    TextStream::instance().setText("Collision: " + std::to_string(player.collision(moveUp, moveDown, moveLeft, moveRight, collisionMap_level1,
                                                                                   nullptr, mapWidth)),3,1);
    TextStream::instance().setText("Jumptimer: " + std::to_string(player.getJumpTimer()),4,1);
    TextStream::instance().setText("IsOnGround: " + std::to_string(player.isOnGround(collisionMap_level1, nullptr,mapWidth)), 5, 1);

    TextStream::instance().setFontColor(BLD_WHITE);
    timer += 1;
    if (timer % 30 == 0) {
        scrollX++;
        bg_dynamics.get()->scroll(scrollX, 0);
    }



    moveLeft = keys & KEY_LEFT;
    moveRight = keys & KEY_RIGHT;
    moveUp = keys & KEY_UP;
    moveDown = keys & KEY_DOWN;
    bPressed = keys & KEY_B;
    //running
    if(bPressed){
        player.move(moveUp, moveDown, moveLeft, moveRight, this->collisionMap_level1, nullptr, bPressed, mapWidth, 0);
    }
    //walking
    else {
        if (timer % 2 == 0) {
            player.move(moveUp, moveDown, moveLeft, moveRight, this->collisionMap_level1, nullptr, bPressed, mapWidth, 0);
        }
    }
    player.isIdle(moveUp, moveDown, moveLeft, moveRight);
    player.setGravity(this->collisionMap_level1, nullptr, mapWidth, 0);
    if(player.calcTileX() == 18 || player.calcTileX() == 19){
        TextStream::instance().setText("PRESS A", 3,17);
        if(keys & KEY_A){

            temple_scene* templeScene = new temple_scene(engine, skin_choice);
            engine->setScene(templeScene);
            TextStream::instance().clear();
            bg_dynamics->scroll(0,0);
        }
    }

    if(player.fellOfMap(this->collisionMap_level1, nullptr, mapWidth)){
        death_scene* deathScene = new death_scene(engine, skin_choice);
        engine->transitionIntoScene(deathScene,new FadeOutScene(2));
        bg_dynamics->scroll(0,0);

    }


};