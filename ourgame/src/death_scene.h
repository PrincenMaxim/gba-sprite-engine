//
// Created by Gebruiker on 20/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class death_scene : public Scene{
private:
    //Sprites
    SpriteBuilder<Sprite> builder;
    std::unique_ptr<Sprite> arrowSprite;

    //Backgrounds
    std::unique_ptr<Background> bg_1;

    int timer = 0;
    int scrollX = 0;
    int scene_timer = 0;
    int skin_choice;
public:
    death_scene(std::shared_ptr<GBAEngine> engine, int skin) : Scene(engine){this->skin_choice = skin;}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
