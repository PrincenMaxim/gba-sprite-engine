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
            .withLocation(0 ,startY)
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

    return 0;
}


void Player::move(bool up, bool down, bool left, bool right, int collision_map[20][30], bool bPressed) {
    if (bPressed) animationSpeed = 2;
    else animationSpeed = 1;
    if (idle) {
        playerWalkingSprite->stopAnimating();
        playerWalkingSprite->animateToFrame(0);
        if (!playerIdleSprite->isAnimating()) playerIdleSprite->makeAnimated(0, 4, 8);
        if (!playerWalkingSprite->isOffScreen())
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY());
        playerWalkingSprite->moveTo(playerIdleSprite->getX(), GBA_SCREEN_HEIGHT + 32);


    }
    else {

        if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
        if (!playerIdleSprite->isOffScreen())
            playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());

        if (playerWalkingSprite->getAnimationDelay() != 8 / getAnimationSpeed()) {
            playerWalkingSprite->stopAnimating();
            playerWalkingSprite->animateToFrame(6);
            playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
        }

        if (right && playerWalkingSprite->getX() < GBA_SCREEN_WIDTH && playerIdleSprite->getX() < GBA_SCREEN_WIDTH - 24
            && collision(up, down, left, right, collision_map) != 1) {

            playerWalkingSprite->flipHorizontally(0);
            playerIdleSprite->flipHorizontally(0);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);


            /*if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            if (!playerIdleSprite->isOffScreen())
                playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());*/
            playerWalkingSprite->moveTo(playerWalkingSprite->getX() + 1, playerWalkingSprite->getY());
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
            posX = posX + 1;


            if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0) {
                if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
                if (!playerIdleSprite->isOffScreen())
                    playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());
                playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() - 1);
                playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
                posY = posY - 1;
            } else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 &&
                       playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32
                       && collision(up, down, left, right, collision_map) != 1) {
                if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
                if (!playerIdleSprite->isOffScreen())
                    playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());
                playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() + 1);
                playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
                posY = posY + 1;
            }

        } else if (left && playerWalkingSprite->getX() > 0 && playerIdleSprite->getX() > 0
                   && collision(up, down, left, right, collision_map) != 1) {

            playerWalkingSprite->flipHorizontally(1);
            playerIdleSprite->flipHorizontally(1);
            playerIdleSprite->stopAnimating();
            playerIdleSprite->animateToFrame(0);
            /*if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            if (!playerIdleSprite->isOffScreen())
                playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());*/
            playerWalkingSprite->moveTo(playerWalkingSprite->getX() - 1, playerWalkingSprite->getY());
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
            posX = posX - 1;

            if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0) {
                if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
                if (!playerIdleSprite->isOffScreen())
                    playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());
                playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() - 1);
                playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
                posY = posY - 1;
            } else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 &&
                       playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32
                       && collision(up, down, left, right, collision_map) != 1) {
                if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
                if (!playerIdleSprite->isOffScreen())
                    playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());
                playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() + 1);
                playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
                posY = posY + 1;
            }
        } else if (up && playerWalkingSprite->getY() > 0 && playerIdleSprite->getY() > 0
                   && collision(up, down, left, right, collision_map) != 1) {

            /*if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            if (!playerIdleSprite->isOffScreen())
                playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());*/
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() - 1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
            posY = posY - 1;
        } else if (down && playerWalkingSprite->getY() <= GBA_SCREEN_HEIGHT + 32 &&
                   playerIdleSprite->getY() <= GBA_SCREEN_HEIGHT + 32
                   && collision(up, down, left, right, collision_map) != 1) {

            /*if (!playerWalkingSprite->isAnimating())playerWalkingSprite->makeAnimated(0, 6, 8 / getAnimationSpeed());
            if (!playerIdleSprite->isOffScreen())
                playerWalkingSprite->moveTo(playerIdleSprite->getX(), playerIdleSprite->getY());*/
            playerWalkingSprite->moveTo(playerWalkingSprite->getX(), playerWalkingSprite->getY() + 1);
            playerIdleSprite->moveTo(playerWalkingSprite->getX(), GBA_SCREEN_HEIGHT + 32);
            posY = posY + 1;
            }
        }


}