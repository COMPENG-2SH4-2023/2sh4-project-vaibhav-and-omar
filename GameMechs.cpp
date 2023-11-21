#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 21;
    boardSizeY = 10;

    exitFlag = 0;
    input = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = 0;
    input = 0;
}

// do you need a destructor?
// No we don't because there are no DMA (dynamically allocated variables)


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}


