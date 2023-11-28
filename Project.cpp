#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 150000

// Global GameMechs object --> on heap
GameMechs* game; 

// Global Player Object --> on heap
Player* player;

// Global Food Object --> on heap
Food* food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(game->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}

// Game Stages

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    game = new GameMechs(); // initialize our GameMechs class
    player = new Player(game); // initialize our player class
    food = new Food(game, player); // initialize our food

    food->generateFood();
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        game->setInput(MacUILib_getChar());
    }else {
        game->clearInput();
    }
}

void RunLogic(void)
{
    if (game->getInput() != 0) {

        // Input Processing Actions START ----------------------

        game->processInput(); // Process input for exiting game and other debugging keys

        if (game->getInput() == 'r') {
            food->generateFood();
        }

        player->updatePlayerDir();

        // Input Processing Actions END ------------------------

        game->clearInput();
    }

    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    if (game->getExitFlagStatus() == 0) {
        // Default draw

        for (int j = 0; j < game->getBoardSizeY(); j++) {
            for (int i = 0; i < game->getBoardSizeX(); i++){
                // Draw object by priority
                objPos current;

                if (( j == 0 ) || ( j == ( game->getBoardSizeY() - 1 ) ) || ( i == 0 ) || ( i == ( game->getBoardSizeX() - 1 ) )) {
                    MacUILib_printf("%c", game->getBorderChar());
                    continue;
                }

                player->getPlayerPos(current);
                if (i == current.x && j == current.y){
                    MacUILib_printf("%c", current.symbol);
                    continue;
                }

                food->getFoodPos(current);
                if (i == current.x && j == current.y) {
                    MacUILib_printf("%c", current.symbol);
                    continue;
                }

                MacUILib_printf("%c", game->getEmptyChar());
            }
            MacUILib_printf("\n");
        }

        MacUILib_printf("Score: %d\n\n", game->getScore());

        // Debug Draw

        MacUILib_printf("==DEBUG==\n\n");
        MacUILib_printf("Player Direction: %d", player->getPlayerDir());
    }else {
        if (game->getLoseFlagStatus() == 0) {
            // Exit game draw
            MacUILib_printf("Game Ended. Score: %d\n\n", game->getScore());
        }else {
            // Lose game draw
            MacUILib_printf("You Died! Score: %d\n\n", game->getScore());
        }
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete food;
    food = nullptr;
    delete player;
    player = nullptr;
    delete game;
    game = nullptr;
    MacUILib_uninit();
}
