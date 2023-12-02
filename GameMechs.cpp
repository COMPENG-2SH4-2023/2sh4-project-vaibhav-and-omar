#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 30; // recommended board size in manual
    boardSizeY = 15;

    exitFlag = 0;
    loseFlag = 0;

    score = 0;
    input = 0;

    borderChar = '#';
    emptyChar = ' ';
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = 0;
    loseFlag = 0;

    score = 0;
    input = 0;

    borderChar = '#';
    emptyChar = ' ';
}

// do you need a destructor?
// --> No we don't because there are no DMA (dynamically allocated variables)

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

// EXIT AND LOSE FLAGS

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setLoseFlag()
{
    loseFlag = 1;
    exitFlag = 1;
}

// INPUTS

char GameMechs::getInput()
{
    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::processInput()
{
    switch (input) { // just some debugging keys
        case '\e':
            setExitTrue();
            break;
        //case '>':
        //    incrementScore();
        //    break;
        //case '<':
        //    incrementScore(-1);
        //    break;
        //case 'f':
        //    setLoseFlag();
        //    break;
        default:
            break;
    }
}

// SCORE

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1;
}

void GameMechs::incrementScore(int num)
{
    score += num;
}

// GAME CHARACTERS

char GameMechs::getBorderChar() {
    return borderChar;
}

char GameMechs::getEmptyChar() {
    return emptyChar;
}

