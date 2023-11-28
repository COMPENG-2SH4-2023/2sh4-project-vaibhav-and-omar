#include "Food.h"

Food::Food(GameMechs* gameRef, Player* playerRef)
{
    srand(time(NULL));
    foodPos = objPos();
    game = gameRef;
    player = playerRef;
}

void Food::generateFood() {
    objPosArrayList* playerPosList; // get player position list
    objPos playerPos;
    playerPosList = player->getPlayerPos();
    bool restart = 0;

    do {
        restart = 0;
        
        foodPos.setObjPos(
            (rand() % (game->getBoardSizeX() - 2) + 1), // randomize x, y and choose from random ascii character
            (rand() % (game->getBoardSizeY() - 2) + 1),
            (char) (rand() % (126 - 33) + 33)
        );

        for (int i = 0; i < playerPosList->getSize(); i++){
            playerPosList->getElement(playerPos, i);
            if (playerPos.isPosEqual(&foodPos)) {
                restart = 1;
            }
        }
    } while (restart);
}

void Food::getFoodPos(objPos &returnPos) {
    returnPos.setObjPos(foodPos);
}