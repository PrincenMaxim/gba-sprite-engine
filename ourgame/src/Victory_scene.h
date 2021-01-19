//
// Created by Gebruiker on 19/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include "TempSave.h"

class Victory_scene  : public Scene{
private:
    std::shared_ptr<TempSave> save;
    std::unique_ptr<Background> bg_1;
    int timer = 0;
    int scrollX = 0;
public:
    Victory_scene(std::shared_ptr<GBAEngine>engine, std::shared_ptr<TempSave> tempSave) : Scene(engine){ this->save = tempSave;}
    std::vector<Sprite *> sprites() override ;
    std::vector<Background *> backgrounds() override ;
    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H
