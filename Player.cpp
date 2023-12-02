#include "Player.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef; // initialize references to game and food list
    food = foodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    objPos startingPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(startingPos); // player head starts at middle of screen
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    playerPosList = nullptr;
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

    objPos current; // temporary variable used for iteration through player pos list and food list
    bool overlappingFood = false;

    // Check self-collision (can never collide with first 3 elements of snake -> indexes 0 - 2)
    for (int i = 3; i < playerPosList->getSize(); i++) { 
        playerPosList->getElement(current, i);
        if (current.isPosEqual(&newHead)) {
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    //check if overlapping with food in foodlist
    objPosArrayList* foodPosList = food->getFoodList();
    for (int i = 0; i < foodPosList->getSize(); i++) {
        foodPosList->getElement(current, i);
        if (current.isPosEqual(&newHead)) {
            switch (current.getSymbol()) { // special food interactions
                case '$':
                    overlappingFood = true;
                    mainGameMechsRef->incrementScore(3);
                    break;
                case '%':
                    // overlappingFood = true; <-- don't do this b/c we want to remove 3 segments not 2
                    mainGameMechsRef->incrementScore(-2);
                    if (playerPosList->getSize() > 3) {
                        for (int j = 0; j < 3; j++) {
                            playerPosList->removeTail(); // remove 3 segments
                        }
                    }
                    break;
                default:
                    overlappingFood = true;
                    mainGameMechsRef->incrementScore();
                    break;
            }
            break;
        }
    }

    // Insert our new head element
    if (myDir != STOP) {
        playerPosList->insertHead(newHead);
        if (!overlappingFood){
            playerPosList->removeTail(); // if we ate food then don't remove tail
        }else {
            food->generate(playerPosList);
        }
    }
}

