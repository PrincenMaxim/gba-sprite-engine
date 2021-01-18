cmake_minimum_required(VERSION 3.15)
project(ourgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(ourgame.elf
        src/Main.cpp
        src/Level1_scene.cpp
        src/Level1_scene.h
        src/backgrounds/level1_input.h
        src/Player.cpp src/Player.h
        src/sprites/pink_guy_sprites.h
        src/backgrounds/level0_input.h
        src/Character_selection_scene.cpp
        src/Character_selection_scene.h
        src/sprites/lvl0_sprites.h
        src/sounds/choose_your_character.h
        src/sprites/owlet_sprites.h
        src/sprites/dude_sprites.h
        src/Title_scene.cpp
        src/Title_scene.h
        src/backgrounds/title_input.h
        src/Death_scene.cpp
        src/Death_scene.h
        src/sprites/death_sprites.h
        src/backgrounds/death_input.h
        src/Instruction_scene.cpp
        src/Instruction_scene.h
        src/backgrounds/instruction_input.h
        src/FloatingIslands_scene.cpp
        src/FloatingIslands_scene.h
        src/backgrounds/floatingIslands_input.h
        src/Temple_scene.cpp src/Temple_scene.h
        src/backgrounds/temple_input.h
        )


target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)


add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
