//
// Created by Gebruiker on 20/12/2020.
//

#include "Title_scene.h"
#include "backgrounds/title_input.h"



std::vector<Sprite *> Title_scene::sprites() {
    return{};
}

std::vector<Background *> Title_scene::backgrounds() {
    return{
        bg_1.get(),
        bg_2.get(),
        bg_3.get()
    };
}

void Title_scene::load(){

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
    bg_1->scroll(0,0);
    bg_2.get()->scroll(0,0);



}

void Title_scene::tick(u16 keys){
    timer ++;
    TextStream::instance().setFontColor(BLD_BG0);


    if(timer%30==0){
        scrollX++;
        bg_2.get()->scroll(scrollX,0);
    }

    if(keys & KEY_START){
            Character_selection_scene *level0Scene = new Character_selection_scene(engine, save);
            TextStream::instance().clear();
            engine->transitionIntoScene(level0Scene, new FadeOutScene(2));
    }


}