//
// Created by Gebruiker on 19/12/2020.
//

#include "level0_scene.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "backgrounds/level0_input.h"
#include "sprites/lvl0_sprites.h"
#include "sounds/choose_your_character.h"
#include "instruction_scene.h"

std::vector<Sprite *> level0_scene::sprites(){
    std::vector<Sprite*> sprites;

    sprites.push_back(arrowSprite.get());
    sprites.push_back(pinkGuySprite.get());
    sprites.push_back(owletSprite.get());
    sprites.push_back(dudeSprite.get());
    return sprites;

};

std::vector<Background *> level0_scene::backgrounds() {
    return {
        bg_1.get(),
        bg_2.get(),
        bg_3.get()
    };
};

void level0_scene::load(){
    engine.get()->enableText();

    TextStream::instance().clear();
    TextStream::instance().setText("CHOOSE YOUR" ,6,9);
    TextStream::instance().setText(" CHARACTER!", 7, 9);

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(level0_sharedPal, sizeof(level0_sharedPal)));
    bg_1 = std::unique_ptr<Background>(new Background(1, level0_staticsTiles, sizeof(level0_staticsTiles),
                                                     level0_statics_map, sizeof(level0_statics_map),
                                                     19, 1, MAPLAYOUT_32X32));
    bg_2 = std::unique_ptr<Background>(new Background(2, level0_cloudsTiles, sizeof(level0_cloudsTiles),
                                                      level0_clouds_map, sizeof(level0_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    bg_3 = std::unique_ptr<Background>(new Background(3, level0_cloudsTiles, sizeof(level0_cloudsTiles),
                                                      level0_clouds_map, sizeof(level0_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));

    arrowSprite = builder
            .withData(arrow_spriteTiles, sizeof(arrow_spriteTiles))
            .withSize(SIZE_16_16)
            .withLocation(64,64)
            .withinBounds()
            .buildPtr();
    arrowSprite->makeAnimated(0,4,6);

    pinkGuySprite = builder
            .withData(pink_guy_idleTiles, sizeof(pink_guy_idleTiles))
            .withSize(SIZE_32_32)
            .withLocation(56,80)
            .withinBounds()
            .buildPtr();
    pinkGuySprite->makeAnimated(0,4,6);

    owletSprite = builder
            .withData(owlet_idleTiles, sizeof(owlet_idleTiles))
            .withSize(SIZE_32_32)
            .withLocation(104,80)
            .withinBounds()
            .buildPtr();

    dudeSprite = builder
            .withData(dude_idleTiles, sizeof(dude_idleTiles))
            .withSize(SIZE_32_32)
            .withLocation(152,80)
            .withinBounds()
            .buildPtr();

    engine->enqueueSound(chooseyourcharacter, sizeof(chooseyourcharacter), 98000);
};

void level0_scene::tick(u16 keys) {
    timer ++;
    if(scene_timer != 0) scene_timer ++;
    if(scene_timer == 15) scene_timer = 0;


    if(timer%30==0){
        scrollX++;
        bg_2.get()->scroll(scrollX,0);
    }

    if(keys & KEY_RIGHT && scene_timer == 0 && arrowSprite->getX() != 160){
        arrowSprite->moveTo(arrowSprite->getX()+48,arrowSprite->getY());
        scene_timer++;
    }
    if(keys & KEY_LEFT && scene_timer == 0 && arrowSprite->getX() != 64){
        arrowSprite->moveTo(arrowSprite->getX()-48,arrowSprite->getY());
        scene_timer++;
    }

    if(arrowSprite->getX() != 64) pinkGuySprite->makeAnimated(0,4,6);
    if(arrowSprite->getX() != 112) owletSprite->makeAnimated(0, 4, 6);
    if(arrowSprite->getX() != 160) dudeSprite->makeAnimated(0, 4, 6);

    if(keys & KEY_A){
        if(arrowSprite->getX() == 64) skin_choice = 0; //pink guy
        else if(arrowSprite->getX() == 112) skin_choice = 1; //owlet
        else if(arrowSprite->getX() == 160) skin_choice = 2; //dude
        instruction_scene* instructionScene = new instruction_scene(engine, skin_choice);
        engine->transitionIntoScene(instructionScene,new FadeOutScene(2));
        bg_2.get()->scroll(0,0);
    }


};
