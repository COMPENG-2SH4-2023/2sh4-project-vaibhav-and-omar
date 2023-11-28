#ifndef FOOD_H
#define FOOD_H

#include <time.h>
#include <stdlib.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food 
{
    private:
        objPos foodPos;
        GameMechs* game;

        char defaultFoodChar;

        objPosArrayList* foodPosList;
    public:
        Food(GameMechs* gameRef);
        ~Food();

        void generateFood(objPosArrayList* player);
        void getFoodPos(objPos &returnPos);
};

#endif