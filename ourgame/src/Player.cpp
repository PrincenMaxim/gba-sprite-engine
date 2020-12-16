//
// Created by Gebruiker on 15/12/2020.
//
#include <cmath>
#include "Player.h"
#include <libgba-sprite-engine/gba_engine.h>
#include "sprites/player_idle_sprite.h"

std::vector<Sprite *>Player::getSprite() {
    std::vector<Sprite *> sprites;
    sprites.push_back(playerIdleSprite.get());
    sprites.push_back(playerWalkingSprite.get());

    return {sprites};
}


void Player::setBuilder(SpriteBuilder<Sprite> builder) {
    playerIdleSprite = builder
            .withData(idleTiles, sizeof(idleTiles))
            .withSize(SIZE_32_32)
            .withLocation(10,40)
            .withinBounds()
            .buildPtr();

    playerWalkingSprite = builder
            .withData(walkTiles, sizeof(walkTiles))
            .withSize(SIZE_32_32)
            .withLocation(10 ,40)
            .withinBounds()
            .buildPtr();

}

void Player::isIdle(bool up, bool down, bool left, bool right) {
    if(!up && !down && !left && !right)idle = true;
    else idle = false;

}

bool Player::canMove(bool up, bool down, bool left, bool right) {
    int arrayNumberX, arrayNumberY;
    arrayNumberX = round((playerWalkingSprite->getX() + 8)*(32/256));
    arrayNumberY = round((playerWalkingSprite->getY() + 8)*(32/256));
    if(down && (collision_map_test[arrayNumberX][arrayNumberY])==1) return false;
    else return true;
}

void Player::move(bool up, bool down, bool left, bool right) {
    if(idle) {
        playerWalkingSprite->stopAnimating();
        playerWalkingSprite->animateToFrame(0);
        if(!playerIdleSprite->isAnimating()) playerIdleSprite->makeAnimated(0,4,8);
        if(!playerWalkingSprite->isOffScreen()) playerIdleSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY());
        playerWalkingSprite->moveTo(playerIdleSprite->getX(), GBA_SCREEN_HEIGHT + 32);


    }
    else if (right && playerWalkingSprite->getX()<GBA_SCREEN_WIDTH && playerIdleSprite->getX()<GBA_SCREEN_WIDTH-24) {
        playerWalkingSprite->flipHorizontally(0);
        playerIdleSprite->flipHorizontally(0);
        playerIdleSprite->stopAnimating();
        playerIdleSprite->animateToFrame(0);

        if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
        if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
        playerWalkingSprite->moveTo(playerWalkingSprite->getX()+1,playerWalkingSprite->getY());
        playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);

        //if(playerWalkingSprite->getX()> GBA_SCREEN_WIDTH- playerWalkingSprite->getWidth()+10)

        if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0) {
            if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
            if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()-1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
        }
        else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 && playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32)  {
            if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
            if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()+1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
        }

    }
    else if (left && playerWalkingSprite->getX()>0 && playerIdleSprite->getX()>0) {
        playerWalkingSprite->flipHorizontally(1);
        playerIdleSprite->flipHorizontally(1);
        playerIdleSprite->stopAnimating();
        playerIdleSprite->animateToFrame(0);
        if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
        if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
        playerWalkingSprite->moveTo(playerWalkingSprite->getX()-1,playerWalkingSprite->getY());
        playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);

        if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0) {
            if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
            if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()-1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
        }
        else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 && playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32) {
            if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
            if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()+1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
        }
    }
    else if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0) {
        if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
        if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
        playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()-1);
        playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
    }
    else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 && playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32) {
        if(!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0,6,8);
        if(!playerIdleSprite->isOffScreen()) playerWalkingSprite->moveTo(playerIdleSprite->getX(),playerIdleSprite->getY());
        playerWalkingSprite->moveTo(playerWalkingSprite->getX(),playerWalkingSprite->getY()+1);
        playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
    }







}