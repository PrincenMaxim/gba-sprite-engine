//
// Created by Gebruiker on 20/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Death_scene.h"
#include "sprites/death_sprites.h"
#include "backgrounds/level0_input.h"
#include <libgba-sprite-engine/gba/tonc_types.h>
#include "Level1_scene.h"
#include "Title_scene.h"



std::vector<Sprite *> Death_scene::sprites(){
    return {arrowSprite.get()};
}

std::vector<Background *> Death_scene::backgrounds(){
    return{bg_1.get()};
}

void Death_scene::load(){
    engine.get()->enableText();
    engine->getTimer()->reset();
    TextStream::instance().clear();

    TextStream::instance().setText(" YOU DIED!  ", 4,9);
    TextStream::instance().setText("TRY AGAIN?", 10,10);
    TextStream::instance().setText("YES", 15,10);
    TextStream::instance().setText("NO", 15,16);

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(death_SharedPal, sizeof(death_SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(level0_sharedPal, sizeof(level0_sharedPal)));
    bg_1 = std::unique_ptr<Background>(new Background(1, level0_cloudsTiles, sizeof(level0_cloudsTiles),
                                                      level0_clouds_map, sizeof(level0_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    arrowSprite = builder
            .withData(death_arrow_spriteTiles, sizeof(death_arrow_spriteTiles))
            .withSize(SIZE_16_16)
            .withLocation(84,100)
            .withinBounds()
            .buildPtr();
    arrowSprite->makeAnimated(0,4,6);

    bg_1.get()->scroll(0,0);
}
void Death_scene::tick(u16 keys){
    TextStream::instance().setFontColor(BLD_BG0);

    if(scene_timer != 0) scene_timer ++;
    if(scene_timer == 15) scene_timer = 0;
    timer += 1;
    if (timer % 30 == 0) {
        scrollX++;
        bg_1.get()->scroll(scrollX, 0);
    }

    if(keys & KEY_RIGHT && scene_timer == 0 && arrowSprite->getX() < 128){
        arrowSprite->moveTo(arrowSprite->getX()+44,arrowSprite->getY());
        scene_timer++;
    }
    if(keys & KEY_LEFT && scene_timer == 0 && arrowSprite->getX() > 84){
        arrowSprite->moveTo(arrowSprite->getX()-44,arrowSprite->getY());
        scene_timer++;
    }
    if(keys & KEY_A){
        if(arrowSprite->getX() == 84) {
            Level1_scene* level1Scene = new Level1_scene(engine, skin_choice);
            engine->transitionIntoScene(level1Scene, new FadeOutScene(2));
        }
        else if(arrowSprite->getX() == 128){
            Title_scene* titleScene = new Title_scene(engine);
            engine->transitionIntoScene(titleScene, new FadeOutScene(2));
        }
    }
}
