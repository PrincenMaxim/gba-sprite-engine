//
// Created by Gebruiker on 20/12/2020.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

#ifndef GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H


class title_scene : public Scene{
private:
    //Backgrounds
    std::unique_ptr<Background> bg_1;
    std::unique_ptr<Background> bg_2;
    std::unique_ptr<Background> bg_3;

    int timer;
    int scrollX;
public:
    title_scene(std::shared_ptr<GBAEngine> engine) : Scene(engine){}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *>  backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_TITLE_SCENE_H
