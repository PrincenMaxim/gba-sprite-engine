//
// Created by Gebruiker on 21/12/2020.
//

#include "Instruction_scene.h"
#include "Level1_scene.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "backgrounds/instruction_input.h"

std::vector<Sprite *> Instruction_scene::sprites(){
    return {};
}

std::vector<Background *> Instruction_scene::backgrounds(){
    return{
      bg_1.get(),
      bg_2.get(),
      bg_3.get()
    };
}

void Instruction_scene::load(){
    engine.get()->enableText();

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(instruction_sharedPal, sizeof(instruction_sharedPal)));

    bg_1 = std::unique_ptr<Background>(new Background(1, instruction_staticsTiles, sizeof(instruction_staticsTiles),
                                                      instruction_statics_map, sizeof(instruction_statics_map),
                                                      19, 1, MAPLAYOUT_32X32));
    bg_2 = std::unique_ptr<Background>(new Background(2, instruction_cloudsTiles, sizeof(instruction_cloudsTiles),
                                                      instruction_clouds_map, sizeof(instruction_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    bg_3 = std::unique_ptr<Background>(new Background(3, instruction_cloudsTiles, sizeof(instruction_cloudsTiles),
                                                      instruction_clouds_map, sizeof(instruction_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    TextStream::instance().setText(" INSTRUCTIONS",6,8);
    TextStream::instance().setText("  ------------",7,7);
    TextStream::instance().setText(" LEFT,RIGHT: MOVE",10,6);
    TextStream::instance().setText(" UP: JUMP",11,6);
    TextStream::instance().setText(" B: SPRINT",12,6);
    TextStream::instance().setText(" A: INTERACT",13,6);


    bg_2.get()->scroll(0,0);
}

void Instruction_scene::tick(u16 keys){
    timer ++;
    //if(scene_timer != 0) scene_timer ++;
    //if(scene_timer == 15) scene_timer = 0;
    if(timer%30==0){
        scrollX++;
        bg_2.get()->scroll(scrollX,0);
    }

    if(keys & KEY_A){
        Level1_scene* level1Scene = new Level1_scene(engine, skin_choice);
        engine->transitionIntoScene(level1Scene,new FadeOutScene(2));
    }
}