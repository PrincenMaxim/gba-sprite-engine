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
#include "fantasyplatformer.h"
#include <iostream>

std::vector<Sprite *> TestScene::sprites(){
    return {};
};

std::vector<Background *> TestScene::backgrounds() {
    return {
        bg_statics.get(),
        bg_dynamics.get(),
        bg_sky.get(),
        bg_sky2.get()
    };
}

void TestScene::load(){
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(TileSetPal, sizeof(TileSetPal)));

    bg_statics = std::unique_ptr<Background>(new Background(0, TileSetTiles, sizeof(TileSetTiles),
                                                            fantasyplatformer_statics, sizeof(fantasyplatformer_statics),
                                                            3,0,MAPLAYOUT_32X32));
    bg_dynamics = std::unique_ptr<Background>(new Background(1, TileSetTiles, sizeof(TileSetTiles),
                                                             fantasyplatformer_dynamics, sizeof(fantasyplatformer_dynamics),
                                                             21,2, MAPLAYOUT_32X32));
    bg_sky = std::unique_ptr<Background>(new Background(2, blauwTiles, sizeof(blauwTiles),
                                                        blauwe_achtergrond, sizeof(blauwe_achtergrond),
                                                        25,3,MAPLAYOUT_32X32));
    bg_sky2 = std::unique_ptr<Background>(new Background(3, blauwTiles, sizeof(blauwTiles),
                                                        blauwe_achtergrond, sizeof(blauwe_achtergrond),
                                                        25,3,MAPLAYOUT_32X32));



};

void TestScene::tick(u16 keys){
    //Scroll voor dynamic background
    scrollXcounter += 1;
    if(scrollXcounter % 50 ==0) {
        scrollX ++;
        bg_dynamics.get()->scroll(scrollX, 0);
    }
    // end scroll dynamic background
};