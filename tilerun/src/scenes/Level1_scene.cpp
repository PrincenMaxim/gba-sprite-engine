//
// Created by Maxim on 15/12/2020.
//

#include "Level1_scene.h"

#include "../backgrounds/level1_input.h"
#include "../sprites/pink_guy_sprites.h"
#include "../sprites/owlet_sprites.h"
#include "../sprites/dude_sprites.h"
#include "Death_scene.h"




std::vector<Sprite *> Level1_scene::sprites(){
    return{player.getSprite()};
};

std::vector<Background *> Level1_scene::backgrounds() {
    return {
            bg_statics.get(),
            bg_dynamics.get(),
            bg_3_filler.get(),
    };
}


void Level1_scene::load(){
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
    engine->getTimer()->reset();
    engine->getTimer()->start();
    save->resetCoins();
    bg_statics->scroll(0,0);
    bg_dynamics.get()->scroll(0,0);

    };

void Level1_scene::tick(u16 keys) {
    //Scroll voor dynamic background

    TextStream::instance().clear();
    /*TextStream::instance().setText("X: " + std::to_string(player.calcTileX()),1,1);
    TextStream::instance().setText("Y: " + std::to_string(player.calcTileY()),2,1);
    TextStream::instance().setText("Collision: " + std::to_string(player.collision(moveUp, moveDown, moveLeft, moveRight, collisionMap_level1,
                                                                                   nullptr, mapWidth)),3,1);
    TextStream::instance().setText("Jumptimer: " + std::to_string(player.getJumpTimer()),4,1);
    TextStream::instance().setText("IsOnGround: " + std::to_string(player.isOnGround(collisionMap_level1, nullptr,mapWidth)), 5, 1);*/
    TextStream::instance().setText(std::to_string(engine->getTimer()->getMinutes())+":"+
                                    std::to_string(engine->getTimer()->getSecs())+":"+
                                    std::to_string(engine->getTimer()->getMsecs()),1,1);
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

            Temple_scene* templeScene = new Temple_scene(engine, save);
            engine->setScene(templeScene);
            TextStream::instance().clear();
            bg_dynamics->scroll(0,0);
        }
    }

    if(player.fellOfMap(this->collisionMap_level1, nullptr, mapWidth)){
        Death_scene* deathScene = new Death_scene(engine, save);
        engine->transitionIntoScene(deathScene,new FadeOutScene(2));


    }


};