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

    public:
        Food(GameMechs* gameRef);

        void generateFood(objPosArrayList* player);
        void getFoodPos(objPos &returnPos);
};

class SuperFood : public Food
{

};

#endif