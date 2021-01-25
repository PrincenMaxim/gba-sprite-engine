//
// Created by Gebruiker on 19/01/2021.
//

#include "Victory_scene.h"
#include "../backgrounds/character_selection_input.h"


std::vector<Sprite *> Victory_scene::sprites(){
    return {};
}
std::vector<Background *> Victory_scene::backgrounds(){
    return{bg_1.get()};
}

void Victory_scene::calcScore() {
    this->score = round(-engine->getTimer()->getTotalMsecs() + 20000) + 1000*save->getCoins();
}

void Victory_scene::calcBestScore() {
    if(score > save->getBestScore())save->setBestScore(score);
}

void Victory_scene::load(){
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(character_selection_sharedPal, sizeof(character_selection_sharedPal)));
    bg_1 = std::unique_ptr<Background>(new Background(1, character_selection_cloudsTiles, sizeof(character_selection_cloudsTiles),
                                                      character_selection_clouds_map, sizeof(character_selection_clouds_map),
                                                      20, 2, MAPLAYOUT_32X32));
    calcScore();
    calcBestScore();
}



void Victory_scene::tick(u16 keys){
    TextStream::instance().setText(" VICTORY!",2,10);
    TextStream::instance().setText("COINS:            "+ std::to_string(save->getCoins()),5,3);
    TextStream::instance().setText("TIME:             "+ std::to_string(engine->getTimer()->getMinutes())+":"+
                                                     std::to_string(engine->getTimer()->getSecs())+":"+
                                                     std::to_string(engine->getTimer()->getMsecs()),7,3);
    TextStream::instance().setText("SCORE:            " + std::to_string(score), 9, 3);
    TextStream::instance().setText("BEST TIMESCORE:   " + std::to_string(save->getBestScore()),13,3);
    TextStream::instance().setText("PRESS A TO CONTINUE", 17, 5);
    TextStream::instance().setFontColor(BLD_BG0);
    timer++;
    if (timer % 30 == 0) {
        scrollX++;
    }
    bg_1.get()->scroll(scrollX, 0);

    if(keys & KEY_A){
        Title_scene* titleScene = new Title_scene(engine, save);
        engine->transitionIntoScene(titleScene, new FadeOutScene(2));
    }
}