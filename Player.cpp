#include "Player.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos = objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    returnPos.setObjPos(playerPos);
}

int Player::getPlayerDir()
{
    return myDir;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    switch (mainGameMechsRef->getInput()) {
        case 'w':
            if (myDir != DOWN) {
                myDir = UP;
            }
            break;
        case 'a':
            if (myDir != RIGHT) {
                myDir = LEFT;
            }
            break;
        case 's':
            if (myDir != UP) {
                myDir = DOWN;
            }
            break;
        case 'd':
            if (myDir != LEFT) {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    switch (myDir) {
        case RIGHT:
            playerPos.x++;
            break;
        case LEFT:
            playerPos.x--;
            break;
        case UP:
            playerPos.y--;
            break;
        case DOWN:
            playerPos.y++;
            break;
        case STOP:
        default:
            break;
    }

    if (playerPos.x >= (mainGameMechsRef->getBoardSizeX() - 1)){
        playerPos.x = playerPos.x % (mainGameMechsRef->getBoardSizeX() - 2);
    }else if (playerPos.x <= 0) {
        playerPos.x = (mainGameMechsRef->getBoardSizeX() - 2) + (playerPos.x % (mainGameMechsRef->getBoardSizeX() - 2));
    }
    
    if (playerPos.y >= (mainGameMechsRef->getBoardSizeY() - 1)){
        playerPos.y = playerPos.y % (mainGameMechsRef->getBoardSizeY() - 2);
    }else if (playerPos.y <= 0) {
        playerPos.y = (mainGameMechsRef->getBoardSizeY() - 2) + (playerPos.y % (mainGameMechsRef->getBoardSizeY() - 2));
    }
}

