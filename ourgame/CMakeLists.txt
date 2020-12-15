cmake_minimum_required(VERSION 3.15)
project(ourgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(ourgame.elf
        src/main.cpp
        src/test_scene.cpp
        src/test_scene.h
        src/fantasyplatformer.h)


target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)


add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
