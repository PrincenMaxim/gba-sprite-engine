//
// Created by Maxim on 15/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "Player.h"

class TestScene : public Scene {
private:
    //Backgrounds
    std::unique_ptr<Background> bg_statics;
    std::unique_ptr<Background> bg_dynamics;
    std::unique_ptr<Background> bg_sky;
    std::unique_ptr<Background> bg_sky2;

    int scrollX = 0;
    int timer =0;
    bool moveLeft = 0;
    bool moveRight = 0;
    bool moveDown = 0;
    bool moveUp = 0;



    //Sprites
    Player player;
    SpriteBuilder<Sprite> builder;

public:
    TestScene(std::shared_ptr<GBAEngine> engine) : Scene(engine){}

    std::vector<Sprite *> sprites() override ;
    std::vector<Background *> backgrounds() override ;

    void move();

    void load() override;
    void tick(u16 keys) override;
};
#endif //GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
