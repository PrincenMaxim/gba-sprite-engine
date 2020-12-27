cmake_minimum_required(VERSION 3.15)
project(ourgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(ourgame.elf
        src/main.cpp
        src/level1_scene.cpp
        src/level1_scene.h
        src/backgrounds/level1_input.h
        src/Player.cpp src/Player.h
        src/sprites/pink_guy_coin_sprites.h
        src/backgrounds/level0_input.h
        src/level0_scene.cpp
        src/level0_scene.h
        src/sprites/lvl0_sprites.h
        src/sounds/choose_your_character.h
        src/sprites/owlet_sprites.h
        src/sprites/dude_sprites.h
        src/title_scene.cpp
        src/title_scene.h
        src/backgrounds/title_input.h src/death_scene.cpp src/death_scene.h src/sprites/death_sprites.h src/backgrounds/death_input.h src/instruction_scene.cpp src/instruction_scene.h src/backgrounds/instruction_input.h src/floatingIslands_scene.cpp src/floatingIslands_scene.h src/backgrounds/floatingIslands_input.h src/temple_scene.cpp src/temple_scene.h src/backgrounds/temple_input.h)


target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)


add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
