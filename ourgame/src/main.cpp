#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "level1_scene.h"
#include "level0_scene.h"
#include "title_scene.h"
#include "floatingIslands_scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    //title_scene* titleScene = new title_scene(engine);
    //engine->setScene(titleScene);

    floatingIslands_scene* floatingIslandsScene = new floatingIslands_scene(engine, 2);
    engine->setScene(floatingIslandsScene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}