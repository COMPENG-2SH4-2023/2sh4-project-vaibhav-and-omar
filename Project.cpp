#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

// Global GameMechs object
// - Destroyed when program terminates and calls destructor
// - NOT on the heap --> literally no need to do so
// - Class members can still be on heap, not affected at all
GameMechs game; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(game.getExitFlagStatus() == false)  
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

    game = GameMechs(); // initialize our GameMechs class
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        game.setInput(MacUILib_getChar());
    }else {
        game.clearInput();
    }
}

void RunLogic(void)
{
    char input = game.getInput();
    if (input != 0) {

        // Input Processing Actions START ----------------------

        switch (input) {
            case '\e':
                game.setExitTrue();
                break;
            case '>':
                game.incrementScore();
                break;
            case '<':
                game.incrementScore(-1);
                break;
            case 'f':
                game.setLoseFlag();
                break;
            default:
                break;
        }

        // Input Processing Actions END ------------------------

        game.clearInput();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    if (game.getExitFlagStatus() == 0) {
        // Default draw

        for (int i = 0; i < game.getBoardSizeY(); i++) {
            for (int j = 0; j < game.getBoardSizeX(); j++){
                // Draw object by priority

                if (( i == 0 ) || ( i == ( game.getBoardSizeY() - 1 ) ) || ( j == 0 ) || ( j == ( game.getBoardSizeX() - 1 ) )) {
                    MacUILib_printf("%c", game.getBorderChar());
                    continue;
                }else {
                    MacUILib_printf("%c", game.getEmptyChar());
                    continue;
                }

            }
            MacUILib_printf("\n");
        }

        MacUILib_printf("Score: %d\n\n", game.getScore());
    }else {
        if (game.getLoseFlagStatus() == 0) {
            // Exit game draw
            MacUILib_printf("Game Ended. Score: %d\n\n", game.getScore());
        }else {
            // Lose game draw
            MacUILib_printf("You Died! Score: %d\n\n", game.getScore());
        }
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_uninit();
}
