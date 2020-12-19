//
// Created by Maxim on 15/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <cmath>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class Player {
private:
    bool idle = true;
    int posX = 0;
    int posY;
    int startY;
    int xVelocity = 1;
    int yVelocity = 2;
    int animationSpeed = 1;
    bool pressedJump = false;
    int jumpTimer=0;
    bool bPressed = false;
    std::string prominentSprite;

public:
    std::unique_ptr<Sprite> playerIdleSprite;
    std::unique_ptr<Sprite> playerWalkingSprite;
    void setBuilder(SpriteBuilder<Sprite> builder, int startY);
    std::vector<Sprite *> getSprite();
    void isIdle(bool up, bool down, bool left, bool right);
    void move(bool up, bool down, bool left, bool right, int collision_map[20][30], bool bPressed);
    int calcTileX();
    int calcTileY();
    void setPosY(int y){this->posY = y;}
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    void setStartY(int y){this->startY = y;}
    int getAnimationSpeed(){return animationSpeed;}
    int getStartY(){return startY;}
    void setGravity(int collision_map[20][30]);
    int collision(bool up, bool down, bool left, bool right, int collision_map[20][30]);
    bool isOnGround(int collision_map[20][30]);
    void jump();
    int getJumpTimer(){return this->jumpTimer;}
    bool getJumped(){return this->pressedJump;};
    int getYvel(){return this->yVelocity;}

    void fellOfMap(int collision_map[20][30]);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
