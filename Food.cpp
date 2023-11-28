#include "Food.h"

Food::Food(GameMechs* gameRef, Player* playerRef)
{
    srand(time(NULL));
    foodPos = objPos();
    game = gameRef;
    player = playerRef;
}

void Food::generateFood() {
    objPos playerPos; // get player position
    player->getPlayerPos(playerPos);

    do {
        foodPos.setObjPos(
            (rand() % (game->getBoardSizeX() - 2) + 1), // randomize x, y and choose from random ascii character
            (rand() % (game->getBoardSizeY() - 2) + 1),
            (char) (rand() % (126 - 33) + 33)
        );
    } while (playerPos.isPosEqual(&foodPos));
}

void Food::getFoodPos(objPos &returnPos) {
    returnPos.setObjPos(foodPos);
}