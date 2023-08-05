#include "Game.h"

// Here is the game loop. As you can see, there is not much code.
// Use this file to get a general idea of the architecture of the game.
// See Game.h and Game.cpp to further understand game logic.

int main(int argc, char* args[]) {
    Game game;
    while (game.running){
        game.pollUserEvents();
        game.logicRun();
        game.updateScreen();
    }
    SDL_Quit();
    return 0;
}
