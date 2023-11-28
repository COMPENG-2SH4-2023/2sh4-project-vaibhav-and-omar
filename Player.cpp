#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;


    // more actions to be included

    playerPosList = new objPosArrayList();

    objPos startingPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(startingPos);
}


Player::~Player()
{
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPosList;
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

    objPos playerPos; // get our player position
    playerPosList->getHeadElement(playerPos);

    objPos newHead(playerPos); // copy it to a temporary head object

    // Calculate new x-y for head position
    switch (myDir) {
        case RIGHT:
            newHead.x++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case STOP:
        default:
            break;
    }

    // implement wrap-around logic
    if (newHead.x >= (mainGameMechsRef->getBoardSizeX() - 1)){
        newHead.x = newHead.x % (mainGameMechsRef->getBoardSizeX() - 2);
    }else if (newHead.x <= 0) {
        newHead.x = (mainGameMechsRef->getBoardSizeX() - 2) + (newHead.x % (mainGameMechsRef->getBoardSizeX() - 2));
    }
    
    if (newHead.y >= (mainGameMechsRef->getBoardSizeY() - 1)){
        newHead.y = newHead.y % (mainGameMechsRef->getBoardSizeY() - 2);
    }else if (newHead.y <= 0) {
        newHead.y = (mainGameMechsRef->getBoardSizeY() - 2) + (newHead.y % (mainGameMechsRef->getBoardSizeY() - 2));
    }

    // Insert our new head element
    if (myDir != STOP) {
        playerPosList->insertHead(newHead);
        playerPosList->removeTail();
    }
}

