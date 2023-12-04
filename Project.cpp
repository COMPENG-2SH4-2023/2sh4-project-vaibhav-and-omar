#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 150000

// NOTES (IMPORTANT PLEASE READ --> WHOEVERS MARKING OR TESTING)
// - There are no leaks in this program (triple checked), however it depends on the platform
// --> if you are on MacOS, when using the leaks tool it should work as expected and give "0 leaks"
// --> if you are linux, when using valgrind, you will see "201 bytes, possibly lost" this is due to the MacUILib library and is out of the projects scope / control (confirmed by Dr. Scott Chen and Dr. Athar)
// --> if you are on windows, we haven't checked with Dr. Memory but it should be the same
// - Additionally you will notice that there are 5 foods on the board at one time, with 1 of them being a special character (superfood)
// --> There are two types of super foods, 1st is a "$" which simply increases score by 3 instead of 1
// --> And the "%" superfood which decreases score but also removes some length from the snake

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
    food = new Food(game); // initialize our food
    player = new Player(game, food); // initialize our player class

    food->generate(player->getPlayerPos()); // generate the first round of food
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
            food->generate(player->getPlayerPos());
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
                objPos current; // temporary variables used for iterating through player and food lists
                objPosArrayList* currentList;
                bool printed = 0;

                if (( j == 0 ) || ( j == ( game->getBoardSizeY() - 1 ) ) || ( i == 0 ) || ( i == ( game->getBoardSizeX() - 1 ) )) {
                    MacUILib_printf("%c", game->getBorderChar()); // print border characters
                    continue;
                }

                currentList = player->getPlayerPos(); // loop through player array list and print characters
                for (int k = 0; k < currentList->getSize(); k++){
                    currentList->getElement(current, k);
                    if (i == current.x && j == current.y){
                        MacUILib_printf("%c", current.symbol);
                        printed = 1;
                        break;
                    }
                }
                if (printed) continue; // we skip if we printed already

                currentList = food->getFoodList(); // loop through food array list and print characters
                for (int k = 0; k < currentList->getSize(); k++){
                    currentList->getElement(current, k);
                    if (i == current.x && j == current.y){
                        MacUILib_printf("%c", current.symbol);
                        printed = 1;
                        break;
                    }
                }
                if (printed) continue;

                MacUILib_printf("%c", game->getEmptyChar()); // if none of the above, then blank space
            }
            MacUILib_printf("\n");
        }

        MacUILib_printf("Score: %d\t", game->getScore());
        MacUILib_printf("Length: %d\n\n", player->getPlayerPos()->getSize());

        if (player->getPlayerDir() == Player::STOP) MacUILib_printf("--PRESS WASD TO MOVE--");

        // Debug Draw
        //MacUILib_printf("==DEBUG==\n\n");
        // MacUILib_printf("Player Direction: %d", player->getPlayerDir());
        //MacUILib_printf("Tiles Remaining: %d", ((game->getBoardSizeX() - 2) * (game->getBoardSizeY() - 2)) - food->getFoodList()->getSize() - player->getPlayerPos()->getSize());
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
    delete player;
    player = nullptr;
    delete food;
    food = nullptr;
    delete game;
    game = nullptr;
    MacUILib_uninit();
}
