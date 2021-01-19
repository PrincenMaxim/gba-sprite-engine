//
// Created by Gebruiker on 19/12/2020.
//

#include "Character_selection_scene.h"


#include "backgrounds/character_selection_input.h"
#include "sprites/lvl0_sprites.h"
#include "sounds/choose_your_character.h"


std::vector<Sprite *> Character_selection_scene::sprites(){
    std::vector<Sprite*> sprites;

    sprites.push_back(arrowSprite.get());
    sprites.push_back(pinkGuySprite.get());
    sprites.push_back(owletSprite.get());
    sprites.push_back(dudeSprite.get());
    return sprites;

};

std::vector<Background *> Character_selection_scene::backgrounds() {
    return {
        bg_1.get(),
        bg_2.get(),
        bg_3.get()
    };
};

void Character_selection_scene::load(){
    engine.get()->enableText();

    TextStream::instance().clear();
    TextStream::instance().setText("CHOOSE YOUR" ,6,9);
    TextStream::instance().setText(" CHARACTER!", 7, 9);

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(character_selection_sharedPal, sizeof(character_selection_sharedPal)));
    bg_1 = std::unique_ptr<Background>(new Background(1, character_selection_staticsTiles, sizeof(character_selection_staticsTiles),
                                                      character_selection_statics_map, sizeof(character_selection_statics_map),
                                                      19, 1, MAPLAYOUT_32X32));
    bg_2 = std::unique_ptr<Background>(new Background(2, character_selection_cloudsTiles, sizeof(character_selection_cloudsTiles),
                                                      character_selection_clouds_map, sizeof(character_selection_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    bg_3 = std::unique_ptr<Background>(new Background(3, character_selection_cloudsTiles, sizeof(character_selection_cloudsTiles),
                                                      character_selection_clouds_map, sizeof(character_selection_clouds_map),
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
    bg_1->scroll(0,0);
    bg_2.get()->scroll(0,0);
};

void Character_selection_scene::tick(u16 keys) {
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
        if(arrowSprite->getX() == 64) save->setSkin(0); //pink guy
        else if(arrowSprite->getX() == 112) save->setSkin(1); //owlet
        else if(arrowSprite->getX() == 160) save->setSkin(2); //dude
        Instruction_scene* instructionScene = new Instruction_scene(engine, save);
        engine->transitionIntoScene(instructionScene,new FadeOutScene(2));
    }
};
