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
    int xVelocity = 2;
    int yVelocity = 2;
    int animationSpeed = 1;
    bool pressedJump = false;
    int jumpTimer=0;
    bool bPressed = false;
    int skin = 21;
    int prevPosX;
    int prevPosY;
    std::string prominentSprite;
    int jumpDirection;

public:
    std::unique_ptr<Sprite> playerIdleSprite;
    std::unique_ptr<Sprite> playerWalkingSprite;
    void setBuilder(SpriteBuilder<Sprite> builder, int startY, int skin);
    std::vector<Sprite *> getSprite();
    void isIdle(bool up, bool down, bool left, bool right);
    void move(bool up, bool down, bool left, bool right, int collision_map_32[20][32],
              int collision_map_[20][64], bool bPressed, int mapWidth, int scrollStatics);
    int calcTileX();
    int calcTileY();
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getPrevPosX(){return prevPosX;}
    int getPrevPosY(){return prevPosY;}
    void setPrevPosX(int x){this->prevPosX=x;}
    void setPrevPosY(int y){this->prevPosY=y;}
    void setPosX(int x){this->posX=x;}
    void setPosY(int y){this->posY=y;}
    void setStartY(int y){this->startY = y;}
    int getAnimationSpeed(){return animationSpeed;}
    int getStartY(){return startY;}
    void setGravity(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth, int scrollStatics);
    int collision(bool up, bool down, bool left, bool right, int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth);
    bool isOnGround(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth);
    void jump();
    int getJumpTimer(){return this->jumpTimer;}
    bool getJumped(){return this->pressedJump;};
    int getYvel(){return this->yVelocity;}
    void setSkin(int i){this->skin = i;}
    int getSkin(){return this->skin;}
    void calcJumpDirection(bool up, bool left, bool right);
    int getJumpDirection(){return this->jumpDirection;}

    bool fellOfMap(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
