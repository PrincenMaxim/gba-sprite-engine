//
// Created by Gebruiker on 20/12/2020.
//

#include "title_scene.h"
#include "backgrounds/title_input.h"
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include "level0_scene.h"

std::vector<Sprite *> title_scene::sprites() {
    return{};
}

std::vector<Background *> title_scene::backgrounds() {
    return{
        bg_1.get(),
        bg_2.get(),
        bg_3.get()
    };
}

void title_scene::load(){

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(title_sharedPal, sizeof(title_sharedPal)));
    bg_1 = std::unique_ptr<Background>(new Background(1, title_staticsTiles,sizeof(title_staticsTiles),
                                                      title_statics,sizeof(title_statics),
                                                      19,1, MAPLAYOUT_32X32));
    bg_2 = std::unique_ptr<Background>(new Background(2, title_cloudsTiles ,sizeof(title_cloudsTiles),
                                                      title_clouds_map,sizeof(title_clouds_map),
                                                      20,2, MAPLAYOUT_32X32));
    bg_3 = std::unique_ptr<Background>(new Background(3, title_cloudsTiles,sizeof(title_cloudsTiles),
                                                      title_clouds_map,sizeof(title_clouds_map),
                                                      20,2, MAPLAYOUT_32X32));
    TextStream::instance().clear();
    TextStream::instance().setText("PRESS START", 15,9);



}

void title_scene::tick(u16 keys){
    timer ++;
    TextStream::instance().setFontColor(BLD_BG0);


    if(timer%30==0){
        scrollX++;
        bg_2.get()->scroll(scrollX,0);
    }

    if(keys & KEY_START){
            level0_scene *level0Scene = new level0_scene(engine);
            TextStream::instance().clear();
            engine->transitionIntoScene(level0Scene, new FadeOutScene(2));
            bg_2.get()->scroll(0,0);
    }


}