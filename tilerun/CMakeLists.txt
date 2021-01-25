cmake_minimum_required(VERSION 3.15)
project(ourgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(ourgame.elf
        src/Main.cpp
        src/scenes/Level1_scene.cpp
        src/scenes/Level1_scene.h
        src/backgrounds/level1_input.h
        src/Player.cpp src/Player.h
        src/sprites/pink_guy_sprites.h
        src/backgrounds/character_selection_input.h
        src/scenes/Character_selection_scene.cpp
        src/scenes/Character_selection_scene.h
        src/sprites/lvl0_sprites.h
        src/sounds/choose_your_character.h
        src/sprites/owlet_sprites.h
        src/sprites/dude_sprites.h
        src/scenes/Title_scene.cpp
        src/scenes/Title_scene.h
        src/backgrounds/title_input.h
        src/scenes/Death_scene.cpp
        src/scenes/Death_scene.h
        src/sprites/death_sprites.h
        src/backgrounds/death_input.h
        src/scenes/Instruction_scene.cpp
        src/scenes/Instruction_scene.h
        src/backgrounds/instruction_input.h
        src/scenes/FloatingIslands_scene.cpp
        src/scenes/FloatingIslands_scene.h
        src/backgrounds/floatingIslands_input.h
        src/scenes/Temple_scene.cpp src/scenes/Temple_scene.h
        src/backgrounds/temple_input.h
        src/TempSave.cpp src/TempSave.h src/scenes/Victory_scene.cpp src/scenes/Victory_scene.h)


target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)


add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
