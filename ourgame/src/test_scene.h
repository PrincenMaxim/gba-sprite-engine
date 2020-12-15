//
// Created by Maxim on 15/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H

#include <libgba-sprite-engine/scene.h>

class TestScene : public Scene {
private:
    std::unique_ptr<Background> bg_statics;
    std::unique_ptr<Background> bg_dynamics;
    std::unique_ptr<Background> bg_sky;
    std::unique_ptr<Background> bg_sky2;
public:
    TestScene(std::shared_ptr<GBAEngine> engine) : Scene(engine){}
    int scrollX = 0;
    int scrollXcounter =0;
    std::vector<Sprite *> sprites() override ;
    std::vector<Background *> backgrounds() override ;


    void load() override;
    void tick(u16 keys) override;
};
#endif //GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
