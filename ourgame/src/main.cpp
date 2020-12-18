#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "test_scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    TestScene* testScene = new TestScene(engine);
    engine->setScene(testScene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}