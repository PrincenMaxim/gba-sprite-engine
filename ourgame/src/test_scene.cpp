//
// Created by Maxim on 15/12/2020.
//

#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "test_scene.h"
#include "backgrounds/fantasyplatformer.h"
#include <iostream>
#include <memory>

#include "sprites/player_idle_sprite.h"
#include "Player.h"



std::vector<Sprite *> TestScene::sprites(){
    return{player.getSprite()};
};

std::vector<Background *> TestScene::backgrounds() {
    return {
            bg_statics.get(),
            bg_dynamics.get(),
            bg_3_filler.get(),
    };
}

void TestScene::move() {
    player.move(moveUp, moveDown, moveLeft, moveRight, this->collision_map_test_scene);


}

void TestScene::load(){
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
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

    player.setBuilder(builder);



    };

void TestScene::tick(u16 keys) {
    //Scroll voor dynamic background
    player.isIdle(moveUp, moveDown, moveLeft, moveRight);
    TextStream::instance().clear();
    TextStream::instance().setText(std::to_string(player.getPosX()), 1, 1);
    TextStream::instance().setFontColor(BLD_WHITE);
    timer += 1;
    if (timer % 50 == 0) {
        scrollX++;
        bg_dynamics.get()->scroll(scrollX, 0);
    }
    if(keys & KEY_B){
        moveLeft = keys & KEY_LEFT;
        moveRight = keys & KEY_RIGHT;
        moveUp = keys & KEY_UP;
        moveDown = keys & KEY_DOWN;
        move();
    }
    else {
    if (timer % 2 == 0) {
        moveLeft = keys & KEY_LEFT;
        moveRight = keys & KEY_RIGHT;
        moveUp = keys & KEY_UP;
        moveDown = keys & KEY_DOWN;
        move();
    }
}
};