#include "Food.h"

Food::Food(GameMechs* gameRef)
{
    srand(time(NULL));
    foodPos = objPos();
    game = gameRef;
    defaultFoodChar = 'o';

    foodPosList = new objPosArrayList();
}

Food::~Food()
{
    delete foodPosList;
};

void Food::generateFood(objPosArrayList* player) {
    objPosArrayList* playerPosList; // get player position list
    objPos playerPos;
    playerPosList = player;
    bool restart = 0;

    do {
        restart = 0;
        
        foodPos.setObjPos(
            (rand() % (game->getBoardSizeX() - 2) + 1), // randomize x, y and choose from random ascii character
            (rand() % (game->getBoardSizeY() - 2) + 1),
            defaultFoodChar
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