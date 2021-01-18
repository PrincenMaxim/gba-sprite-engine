#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "Level1_scene.h"
#include "Character_selection_scene.h"
#include "Title_scene.h"
#include "FloatingIslands_scene.h"
#include "Temple_scene.h"
#include "Instruction_scene.h"

int skinselector;

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    Title_scene* titleScene = new Title_scene(engine);
    engine->setScene(titleScene);

    //Instruction_scene* instructionScene = new Instruction_scene(engine, 2);
    //engine->setScene(instructionScene);

    //Level1_scene* level1Scene = new Level1_scene(engine,0);
    //engine->setScene(level1Scene);

    //Temple_scene* templeScene = new Temple_scene(engine,2);
    //engine->setScene(templeScene);

    //FloatingIslands_scene* floatingIslandsScene = new FloatingIslands_scene(engine, 2);
    //engine->setScene(floatingIslandsScene);



    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}