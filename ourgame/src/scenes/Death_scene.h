//
// Created by Gebruiker on 20/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "../TempSave.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "Level1_scene.h"
#include "Title_scene.h"

class Death_scene : public Scene{
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
    std::shared_ptr<TempSave> save;
public:
    Death_scene(std::shared_ptr<GBAEngine> engine, std::shared_ptr<TempSave> tempSave) : Scene(engine){ this->save = tempSave;
                                                                                                        this->skin_choice = save->getSkin();}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
