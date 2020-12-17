//
// Created by Maxim on 15/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class Player {
private:
    bool idle;
    int posX;
    int posY;

public:
    std::unique_ptr<Sprite> playerIdleSprite;
    std::unique_ptr<Sprite> playerWalkingSprite;
    void setBuilder(SpriteBuilder<Sprite> builder);
    std::vector<Sprite *> getSprite();
    void isIdle(bool up, bool down, bool left, bool right);
    void move(bool up, bool down, bool left, bool right, int collisionMap[20][30]);
    bool canMove(bool up, bool down, bool left, bool right, int collisionMap[20][30]);
    int getPosX(){return posX;}
    int getPosY(){return posY;}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
