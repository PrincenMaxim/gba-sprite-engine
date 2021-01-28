//
// Created by Gebruiker on 15/12/2020.
//

#include "Player.h"
#include "sprites/pink_guy_sprites.h"
#include "sprites/owlet_sprites.h"
#include "sprites/dude_sprites.h"

std::vector<Sprite *>Player::getSprite() {
    std::vector<Sprite *> sprites;
    sprites.push_back(playerIdleSprite.get());
    sprites.push_back(playerWalkingSprite.get());

    return {sprites};
}


void Player::setBuilder(SpriteBuilder<Sprite> builder, int startY, int skin) {
    switch(skin){
        case 0 :
            playerIdleSprite = builder
                    .withData(pink_guy_idleTiles, sizeof(pink_guy_idleTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            playerWalkingSprite = builder
                    .withData(pink_guy_walkTiles, sizeof(pink_guy_walkTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            break;
        case 1 :
            playerIdleSprite = builder
                    .withData(owlet_idleTiles, sizeof(owlet_idleTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            playerWalkingSprite = builder
                    .withData(owlet_walkTiles, sizeof(owlet_walkTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            break;
        case 2 :
            playerIdleSprite = builder
                    .withData(dude_idleTiles, sizeof(dude_idleTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            playerWalkingSprite = builder
                    .withData(dude_walkTiles, sizeof(dude_walkTiles))
                    .withSize(SIZE_32_32)
                    .withLocation(0,startY)
                    .withinBounds()
                    .buildPtr();
            break;

    }
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

int Player::collision(bool up, bool down, bool left, bool right, int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth) {
    if(calcTileX()>=0) {
        if (mapWidth == 256) {
            if(!isOnGround(collision_map_32, collision_map_64, mapWidth)){
                if(calcTileY()>=0){
                    if (left && collision_map_32[calcTileY()][calcTileX()-1] == 1) return 1;
                    else if (right && collision_map_32[calcTileY()][calcTileX() + 1] == 1  ) return 1;
                    else return 0;
                }
                else return 0;
            }
            else {
                if (right && collision_map_32[calcTileY()-1][calcTileX() + 1] == 1) return 1;
                else if (left && collision_map_32[calcTileY()-1][calcTileX() - 1] == 1) return 1;

                else if (up && collision_map_32[calcTileY() - 4][calcTileX()] == 1 && calcTileY() >= 4)
                    return 1;// calcTileY()-4 for character tile height

                else if (down && collision_map_32[calcTileY()][calcTileX()] == 1) return 1;

                else return 0;
            }


        } else if (mapWidth == 512) {
            if(!isOnGround(collision_map_32, collision_map_64, mapWidth)){
                if(calcTileY()>=0){
                    if (left && collision_map_64[calcTileY()][calcTileX()-1] == 1) return 1;
                    else if (right && collision_map_64[calcTileY()][calcTileX() + 1] == 1  ) return 1;
                    else return 0;
                }
                else return 0;
            }
            else {
                if (right && collision_map_64[calcTileY()-1][calcTileX() + 1] == 1) return 1;
                else if (left && collision_map_64[calcTileY()-1][calcTileX() - 1] == 1) return 1;

                else if (up && collision_map_64[calcTileY() - 4][calcTileX()] == 1 && calcTileY() >= 4)
                    return 1;// calcTileY()-4 for character tile height

                else if (down && collision_map_64[calcTileY()][calcTileX()] == 1) return 1;

                else return 0;
            }
        }
        else return 0;
    }
    else return 0;
}

bool Player::isOnGround(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth) {
    if(calcTileY()>=0) {
        if (mapWidth == 256) {
            int playerTileY = calcTileY();
            int playerTileX = calcTileX();
            if ((collision_map_32[playerTileY][playerTileX] == 1)&& playerTileX >= 0 && playerTileY >= -4) return 1;
            else return 0;
        } else if (mapWidth == 512) {
            int playerTileY = calcTileY();
            int playerTileX = calcTileX();
            if ((collision_map_64[playerTileY][playerTileX] == 1)&& playerTileX >= 0 && playerTileY >= -4) return 1;
            else return 0;
        } else return 0;
    }
    else return 0;
}

void Player::setGravity(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth, int scrollStatics){

    if( this->prominentSprite == "idle") {
        playerIdleSprite->moveTo(posX-scrollStatics,posY);
        playerWalkingSprite->moveTo(posX,GBA_SCREEN_HEIGHT+32);
    }

    if( this->prominentSprite == "walk") {
        playerWalkingSprite->moveTo(posX-scrollStatics,posY);
        playerIdleSprite->moveTo(posX,GBA_SCREEN_HEIGHT+32);
    }
    if(mapWidth == 256){
        if (!isOnGround(collision_map_32, collision_map_64, mapWidth) && !pressedJump &&
            collision_map_32[calcTileY()][calcTileX()] != 1 ) {
            posY += yVelocity;
        }
        if (pressedJump) {
            jumpTimer++;
            if (!isOnGround(collision_map_32, collision_map_64,
                            mapWidth && collision_map_32[calcTileY()][calcTileX()] != 1)) {
                if(calcTileY() <= 4){
                    if (jumpTimer <= 6) posY -= 2 * yVelocity;
                    if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                    if (jumpTimer == 15);
                    if (jumpTimer == 16);
                    if (jumpTimer > 16) posY += yVelocity;
                }
                else {
                    if (jumpDirection == 0) {
                        if (collision_map_32[calcTileY() - 3][calcTileX()] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    }
                    if (jumpDirection == 1) {
                        if (collision_map_32[calcTileY() - 3][calcTileX() - 1] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    }
                    if (jumpDirection == 2) {
                        if (collision_map_32[calcTileY() - 3][calcTileX() + 1] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    }
                }
            }

        }
    }
    else if(mapWidth == 512) {
        if (!isOnGround(collision_map_32, collision_map_64, mapWidth) && !pressedJump &&
            collision_map_64[calcTileY()][calcTileX()] != 1) {
            posY += yVelocity;
        }
        if (pressedJump) {
            jumpTimer++;
            if (!isOnGround(collision_map_32, collision_map_64,
                            mapWidth && collision_map_64[calcTileY()][calcTileX()] != 1)) {
                if(calcTileY() <= 4){
                    if (jumpTimer <= 6) posY -= 2 * yVelocity;
                    if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                    if (jumpTimer == 15);
                    if (jumpTimer == 16);
                    if (jumpTimer > 16) posY += yVelocity;
                }
                else {
                    if (jumpDirection == 0) {
                        if (collision_map_64[calcTileY() - 3][calcTileX()] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    } else if (jumpDirection == 1) {
                        if (collision_map_64[calcTileY() - 3][calcTileX() - 1] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    } else if (jumpDirection == 2) {
                        if (collision_map_64[calcTileY() - 3][calcTileX() + 1] != 1) {
                            if (jumpTimer <= 6) posY -= 2 * yVelocity;
                            if (jumpTimer > 6 && jumpTimer <= 14) posY -= 1 * yVelocity;
                            if (jumpTimer == 15);
                            if (jumpTimer == 16);
                            if (jumpTimer > 16) posY += yVelocity;
                        } else {
                            posY += yVelocity;
                            jumpTimer = 16;
                        }
                    }
                }
            }

        }
    }


        if (isOnGround(collision_map_32, collision_map_64, mapWidth)) {
            pressedJump = false;
            jumpTimer = 0;
        }
}

void Player::jump(){
    if(pressedJump == false && jumpTimer == 0) {
        this->pressedJump = true;
    }
}

void Player::move(bool up, bool down, bool left, bool right, int collision_map_32[20][32], int collision_map_64[20][64],
                  bool bPressed, int mapWidth, int scrollStatics) {
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
        playerWalkingSprite->moveTo(posX-scrollStatics, GBA_SCREEN_HEIGHT + 32);
        if (!playerIdleSprite->isAnimating()) playerIdleSprite->makeAnimated(0, 4, 8);
            playerIdleSprite->moveTo(0, posY);

    }
    else {

        if(collision(up,down,left,right,collision_map_32, collision_map_64, mapWidth) == 0 && posX>=0){
            this->prominentSprite = "walk";
        }
        else this->prominentSprite = "idle";


        if (playerWalkingSprite->getAnimationDelay() != 8 / getAnimationSpeed()) {
            playerWalkingSprite->stopAnimating();
            playerWalkingSprite->animateToFrame(6);
            playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
        }

        if (right && up && posX <= mapWidth
            && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1
            && isOnGround(collision_map_32, collision_map_64, mapWidth) && !pressedJump ) {

            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            posX = posX + xVelocity;
            posY = posY - yVelocity;
            jump();
            playerWalkingSprite->moveTo(posX-scrollStatics, posY);
        }

        else if (left && up  && posX > 0
                   && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1
                   && !pressedJump && isOnGround(collision_map_32, collision_map_64, mapWidth)) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            jump();
            posX = posX - xVelocity;
            posY = posY - yVelocity;
            playerWalkingSprite->moveTo(posX-scrollStatics, posY);
        }

        else if (right && posX < mapWidth
                   && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);

            playerWalkingSprite->flipHorizontally(0);
            playerIdleSprite->flipHorizontally(0);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);


            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());

            posX = posX + xVelocity;
            playerWalkingSprite->moveTo(posX-scrollStatics , posY);

        }

        else if (left && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1 && posX>=0) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);

            playerWalkingSprite->flipHorizontally(1);
            playerIdleSprite->flipHorizontally(1);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);

            if (!playerWalkingSprite->isAnimating())playerWalkingSprite
            ->makeAnimated(0, 6, 8 / getAnimationSpeed());


            posX = posX - xVelocity;
            playerWalkingSprite->moveTo(posX-scrollStatics, posY);

        }

        else if (up  && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1 && !pressedJump &&
                   isOnGround(collision_map_32, collision_map_64, mapWidth)) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            posY = posY - yVelocity;
            jump();
            playerWalkingSprite->moveTo(posX-scrollStatics, posY);
        }

        else if (down && posY <= GBA_SCREEN_HEIGHT + 32
                   && collision(up, down, left, right, collision_map_32, collision_map_64, mapWidth) != 1) {
            playerIdleSprite->moveTo(0, GBA_SCREEN_HEIGHT + 32);
            if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            posY = posY + yVelocity;
            playerWalkingSprite->moveTo(posX-scrollStatics, posY);
        }
    }
}

bool Player::fellOfMap(int collision_map_32[20][32], int collision_map_64[20][64], int mapWidth ) {
    if (calcTileY() > 0) {
        if (mapWidth == 256) {
            if (collision_map_32[calcTileY()][calcTileX()] == 2) {
                return 1;
            } else return 0;
        } else if (mapWidth == 512) {
            if (collision_map_64[calcTileY()][calcTileX()] == 2) {
                return 1;
            } else return 0;
        } else return 0;
    }
    else return 0;
}
