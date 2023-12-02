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
        GameMechs* game;

        char defaultFoodChar;
        char specialFood1;
        char specialFood2;

        int numOfRegular;
        int numOfSpecial;

        objPosArrayList* foodPosList;
    public:
        Food(GameMechs* gameRef);
        ~Food();

        void generate(objPosArrayList* player);
        objPosArrayList* getFoodList();
};

#endif