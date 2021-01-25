//
// Created by Gebruiker on 19/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECTION_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECTION_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "../TempSave.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Instruction_scene.h"



class Character_selection_scene : public Scene {
private:
    //Sprites
    SpriteBuilder<Sprite> builder;
    std::unique_ptr<Sprite> arrowSprite;
    std::unique_ptr<Sprite> pinkGuySprite;
    std::unique_ptr<Sprite> owletSprite;
    std::unique_ptr<Sprite> dudeSprite;

    //Backgrounds
    std::unique_ptr<Background> bg_1;
    std::unique_ptr<Background> bg_2;
    std::unique_ptr<Background> bg_3;

    int skin_choice;
    int scene_timer = 0;
    int scrollX = 0;
    int timer = 0;
    std::shared_ptr<TempSave> save;
public:
    Character_selection_scene(std::shared_ptr<GBAEngine> engine, std::shared_ptr<TempSave> tempSave) : Scene(engine){this->save = tempSave;}
    std::vector<Sprite *> sprites() override ;
    std::vector<Background *> backgrounds() override ;


    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECTION_SCENE_H
