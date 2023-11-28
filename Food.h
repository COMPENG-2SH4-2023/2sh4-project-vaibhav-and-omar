#ifndef FOOD_H
#define FOOD_H

#include <time.h>
#include <stdlib.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

class Food 
{
    private:
        objPos foodPos;
        GameMechs* game;
        Player* player;

    public:
        Food(GameMechs* gameRef, Player* playerRef);

        void generateFood();
        void getFoodPos(objPos &returnPos);
};

class SuperFood : public Food
{

};

#endif