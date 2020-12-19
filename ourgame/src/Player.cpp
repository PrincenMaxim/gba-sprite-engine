//
// Created by Gebruiker on 15/12/2020.
//

#include "Player.h"
#include <libgba-sprite-engine/gba_engine.h>
#include "sprites/player_idle_sprite.h"

std::vector<Sprite *>Player::getSprite() {
    std::vector<Sprite *> sprites;
    sprites.push_back(playerIdleSprite.get());
    sprites.push_back(playerWalkingSprite.get());

    return {sprites};
}


void Player::setBuilder(SpriteBuilder<Sprite> builder, int startY) {
    playerIdleSprite = builder
            .withData(idleTiles, sizeof(idleTiles))
            .withSize(SIZE_32_32)
            .withLocation(0,startY)
            .withinBounds()
            .buildPtr();

    playerWalkingSprite = builder
            .withData(walkTiles, sizeof(walkTiles))
            .withSize(SIZE_32_32)
            .withLocation(0,startY)
            .withinBounds()
            .buildPtr();

    setStartY(startY);
    setPosY(startY);
}



void Player::isIdle(bool up, bool down, bool left, bool right) {
    if(!up && !down && !left && !right)idle = true;
    else idle = false;

}

int Player::calcTileX() {
    return round(posX/8);
}

int Player::calcTileY(){
    return round(posY/8);
}

int Player::collision(bool up, bool down, bool left, bool right, int collision_map[20][30]) {

    if (up && collision_map[calcTileY()-4][calcTileX()] == 1) return 1;// calcTileY()-4 for character tile height

    if (down && collision_map[calcTileY()][calcTileX()] == 1) return 1;

    if (right && collision_map[calcTileY()-1][calcTileX()+1]==1) return 1;

    if (left && collision_map[calcTileY()-1][calcTileX()-1]==1) return 1;

    if(!isOnGround(collision_map) && left && collision_map[calcTileY()][calcTileX()-1]==1) return 1;

    if(!isOnGround(collision_map) && right && collision_map[calcTileY()][calcTileX()+1]==1) return 1;

    return 0;
}

bool Player::isOnGround(int collision_map[20][30]) {
    int playerTileY = calcTileY();
    int playerTileX = calcTileX();
    if(collision_map[playerTileY][playerTileX] == 1) return 1;
    else return 0;
}

void Player::setGravity(int collision_map[20][30]){

    if( this->prominentSprite == "idle") {
        playerIdleSprite->moveTo(posX,posY);
        playerWalkingSprite->moveTo(posX,GBA_SCREEN_HEIGHT+32);
    }

    if( this->prominentSprite == "walk") {
        playerWalkingSprite->moveTo(posX,posY);
        playerIdleSprite->moveTo(posX,GBA_SCREEN_HEIGHT+32);
    }

    if(!isOnGround(collision_map) && !pressedJump){
        posY = posY + yVelocity;
    }
    if(pressedJump){
        jumpTimer ++;
        if(!isOnGround(collision_map)) {
            if (jumpTimer == 2) posY -= 2* yVelocity;
            if (jumpTimer >2 && jumpTimer <= 14) posY -= 1* yVelocity;
            if (jumpTimer == 15) ;
            if (jumpTimer == 16) ;
            if (jumpTimer > 16) posY += yVelocity;
        }
    }

    if(isOnGround(collision_map)){
        pressedJump = false;
        jumpTimer = 0;
    }
}

void Player::jump(){
    if(pressedJump == false && jumpTimer == 0) {
        this->pressedJump = true;
    }
}

void Player::move(bool up, bool down, bool left, bool right, int collision_map[20][30], bool bPressed) {
    if (bPressed){
        animationSpeed = 2;
        this->bPressed = true;
    }
    else {
        animationSpeed = 1;
        this->bPressed = false;
    }

    if (idle) {
        this->prominentSprite = "idle";
        playerWalkingSprite->stopAnimating();
        playerWalkingSprite->animateToFrame(0);
        playerWalkingSprite->moveTo(posX, GBA_SCREEN_HEIGHT + 32);
        if (!playerIdleSprite->isAnimating()) playerIdleSprite->makeAnimated(0, 4, 8);
            playerIdleSprite->moveTo(posX, posY);

    }
    else {

        if(collision(up,down,left,right,collision_map) == 0 && posX>=0){
            this->prominentSprite = "walk";
        }
        else this->prominentSprite = "idle";


        if (playerWalkingSprite->getAnimationDelay() != 8 / getAnimationSpeed()) {
            playerWalkingSprite->stopAnimating();
            playerWalkingSprite->animateToFrame(6);
            playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
        }

        if (right && up && posY > 0 && posX < GBA_SCREEN_WIDTH - 24
            && collision(up, down, left, right, collision_map) != 1
            && isOnGround(collision_map) && !pressedJump ) {

            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            posX = posX + xVelocity;
            posY = posY - yVelocity;
            jump();
            setGravity(collision_map);
            playerWalkingSprite->moveTo(posX, posY);



        }

        else if (left && up && posY > 0 && posX > 0
                   && collision(up, down, left, right, collision_map) != 1
                   && !pressedJump && isOnGround(collision_map)) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            posX = posX - xVelocity;
            posY = posY - yVelocity;
            jump();
            playerWalkingSprite->moveTo(posX, posY);


        }

        else if (right && posX < GBA_SCREEN_WIDTH
                   && collision(up, down, left, right, collision_map) != 1) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);

            playerWalkingSprite->flipHorizontally(0);
            playerIdleSprite->flipHorizontally(0);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);


            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());

            posX = posX + xVelocity;
            playerWalkingSprite->moveTo(posX , posY);

        }

        else if (left && collision(up, down, left, right, collision_map) != 1 && posX>=0) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);

            playerWalkingSprite->flipHorizontally(1);
            playerIdleSprite->flipHorizontally(1);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);

            if (!playerWalkingSprite->isAnimating())playerWalkingSprite
            ->makeAnimated(0, 6, 8 / getAnimationSpeed());


            posX = posX - xVelocity;
            playerWalkingSprite->moveTo(posX, posY);

        }

        else if (up  && collision(up, down, left, right, collision_map) != 1 && !pressedJump &&
                   isOnGround(collision_map)) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            posY = posY - yVelocity;
            jump();
            setGravity(collision_map);
            playerWalkingSprite->moveTo(posX, posY);
        }

        else if (down && posY <= GBA_SCREEN_HEIGHT + 32
                   && collision(up, down, left, right, collision_map) != 1) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            posY = posY + yVelocity;
            playerWalkingSprite->moveTo(posX, posY);
        }
    }
}

void Player::fellOfMap(int collision_map[20][30] ) {
    if(collision_map[calcTileY()][calcTileX()]==2){
        posX = 0;
        posY = startY;
    }
}