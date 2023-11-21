#include "Player.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos = objPos(5, 5, '@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    if (myDir != STOP) {
        switch (myDir) {
            case UP:
                playerPos.y--;
                break;
            case DOWN:
                playerPos.y++;
                break;
            case LEFT:
                playerPos.x--;
                break;
            case RIGHT:
                playerPos.x++;
                break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

