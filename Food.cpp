#include "Food.h"

Food::Food(GameMechs* gameRef)
{
    srand(time(NULL)); // seed the random number generator
    game = gameRef;

    defaultFoodChar = 'o';

    numOfRegular = 4;
    numOfSpecial = 1;

    specialFood1 = '$';
    specialFood2 = '%';

    foodPosList = new objPosArrayList();
}

Food::~Food()
{
    delete foodPosList;
    foodPosList = nullptr;
};

objPosArrayList* Food::getFoodList() {
    return foodPosList;
}

void Food::generate(objPosArrayList* player) {
    objPosArrayList* playerPosList; // get player position list
    playerPosList = player;
    objPos temp;
    objPos current;
    bool restart = 0;

    int remaining = ((game->getBoardSizeX() - 2) * (game->getBoardSizeY() - 2)) - foodPosList->getSize() - playerPosList->getSize(); // total # of board spaces - used

    for (int i = 0; i < numOfRegular + numOfSpecial; i++) { // reset list on each generation
        foodPosList->removeTail();
    }

    int regular = (remaining <= (numOfRegular + numOfSpecial + 3)) ? remaining - 3: numOfRegular; // how many regular and special food to spawn
    int special = (remaining <= (numOfRegular + numOfSpecial + 3)) ? 0 : numOfSpecial;

    for (int j = 0; j < regular; j++){ // spawning regular food
        do {
            restart = 0;

            current.setObjPos( // generate a random position
                (rand() % (game->getBoardSizeX() - 2) + 1),
                (rand() % (game->getBoardSizeY() - 2) + 1),
                defaultFoodChar
            );

            // check if the random position collides with our player positions
            for (int i = 0; i < playerPosList->getSize(); i++){
                playerPosList->getElement(temp, i);
                if (temp.isPosEqual(&current)) {
                    restart = 1;
                    break;
                }
            }

            // check if the random position collides with previously generated food
            for (int i = 0; i < foodPosList->getSize(); i++){
                foodPosList->getElement(temp, i);
                if (temp.isPosEqual(&current) || restart) {
                    restart = 1;
                    break;
                }
            }
        } while (restart);

        // if all checks pass for random position, append it to food list
        foodPosList->insertTail(current);
    }

    for (int j = 0; j < special; j++){ // spawning special food
        do {
            restart = 0;

            current.setObjPos( // generate a random position and randomly choose a special food
                (rand() % (game->getBoardSizeX() - 2) + 1),
                (rand() % (game->getBoardSizeY() - 2) + 1),
                (rand() % 2 == 0) ? specialFood1 : specialFood2
            );

            // check if the random position collides with our player positions
            for (int i = 0; i < playerPosList->getSize(); i++){
                playerPosList->getElement(temp, i);
                if (temp.isPosEqual(&current)) {
                    restart = 1;
                    break;
                }
            }

            // check if the random position collides with previously generated food
            for (int i = 0; i < foodPosList->getSize(); i++){
                foodPosList->getElement(temp, i);
                if (temp.isPosEqual(&current) || restart) {
                    restart = 1;
                    break;
                }
            }
        } while (restart);

        // if all checks pass for random position, append it to food list
        foodPosList->insertTail(current);
    }
    
}