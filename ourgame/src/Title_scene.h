//
// Created by Gebruiker on 20/12/2020.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "TempSave.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H


class Title_scene : public Scene{
private:
    //Backgrounds
    std::unique_ptr<Background> bg_1;
    std::unique_ptr<Background> bg_2;
    std::unique_ptr<Background> bg_3;

    int timer;
    int scrollX;
    std::shared_ptr<TempSave> save;
public:
    Title_scene(std::shared_ptr<GBAEngine> engine, std::shared_ptr<TempSave> tempSave) : Scene(engine){this->save=tempSave;}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *>  backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H
