#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "Game.h"
#include "Lasers.h"

using namespace std;

int main(int argc, char* args[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) cout << "SDL_Init FAILED: " << SDL_GetError() << endl;
    if (!(IMG_Init(IMG_INIT_PNG))) cout << "IMG_Init FAILED: " << SDL_GetError() << endl;
    if (TTF_Init() < 0) cout << TTF_GetError() << endl;

    Game game;

    cout << "Refresh Rate: " << game.window->getRefreshRate() << endl;

    SDL_Event event;

    const float deltaTime = 0.01;
    float accumulator = 0.0;
    float currentTime = utils::timeInSeconds();

    bool wPressed, sPressed, dPressed, aPressed, spacePressed, shiftPressed;
    wPressed = sPressed = dPressed = aPressed = spacePressed = shiftPressed = false;

    //game loooooooop
    //IF GAME IS TAKING A LOT OF CPU: comment out all console logs

    while (game.running){

        int startTicks = SDL_GetTicks(); //ticks at start of frame

        float newTime = utils::timeInSeconds();
        float frameTime = newTime - currentTime;

        if (frameTime > 0.25) frameTime = 0.25;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {

            //char0.getPos().print();
            //cout << playerSpeed << endl;
            //if (char0.collides(catBed)) cout << "collision detected" << endl;


            accumulator -= deltaTime;
        }
            while (SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    game.running = false;
                    cout << "Session time: [" << utils::timeInSeconds() << " seconds]" << endl;
                }
                if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_x){
                        game.running = false;
                    }
                    if (event.key.keysym.sym == SDLK_w){
                        wPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_a){
                        aPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_d){
                        dPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        if (game.gameOver == true) game.restartRun(game.obstacles);
                    }
                    if (event.key.keysym.sym == SDLK_SPACE && game.assets->char0.getPos().y >= 100){
                        spacePressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_c){
                        game.primRects.clear();
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT && shiftPressed == false){
                        shiftPressed = true;
                    }
                }
                if (event.type == SDL_KEYUP){
                    if (event.key.keysym.sym == SDLK_w){
                        wPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_a){
                        aPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        sPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_d){
                        dPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE){
                        spacePressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT){
                        shiftPressed = false;	
                    }
                }
            }
        if (!game.gameOver) {
            if (utils::timeInSeconds() - game.timeSinceSpeedIncrease > game.speedIncreaseDelay) {
                game.gameSpeed -= game.speedIncreaseAmt;
                game.timeSinceSpeedIncrease = utils::timeInSeconds();
            }
        }

        game.assets->char0.movePos(game.playerSpeed);
        for (deque<Entity*>::iterator it = game.obstacles.begin(); it != game.obstacles.end(); ++it){
            (**it).movePos(game.gameSpeed, 0);
            if ((*it)->collides(game.assets->char0) && game.gameOver == false) {
                game.gameOver = true;
                cout << "collided with laser" << endl;
            }
        }

        if (spacePressed){
            if (!game.gameOver) {
                if (game.playerSpeed < 5.5) {
                    game.playerSpeed += 0.4;
                }
                else game.playerSpeed = 5.5;
            }
        }
        else {
            if (game.playerSpeed > -5.5) {
                game.playerSpeed -= 0.4;
            }
            else game.playerSpeed = -5.5;
        }

        if (game.gameSpeed != 0){
            if (utils::timeInSeconds() - game.laserTime >= game.laserDelay) {
                int laserType = rand() % 4;
                Entity* newEnt = nullptr;
                int randY = game.playSpace.y + (rand() % ( game.playSpace.h - game.playSpace.y ));
                if (laserType == 0) newEnt = new LaserHorizontal(Vector2f((float)game.width, randY), game.assets);
                else if (laserType == 1) newEnt = new LaserVertical(Vector2f((float)game.width, randY), game.assets);
                else if (laserType == 2) newEnt = new LaserNegativeSlope(Vector2f((float)game.width, randY), game.assets);
                else if (laserType == 3) newEnt = new LaserPositiveSlope(Vector2f((float)game.width, randY), game.assets);
                game.obstacles.push_back(newEnt);
                game.laserTime = utils::timeInSeconds();
            }
        }

        if (game.gameOver) {
            spacePressed = false;
            if ( game.gameSpeed < 0 ) {
                game.gameSpeed += game.slideFactor;
            }
            if ( game.gameSpeed > 0 ) game.gameSpeed = 0;
        }

        // bring out of bounds character back into scope BEFORE rendering:
        float checkY = game.assets->char0.getPos().y;
        if (checkY + game.assets->char0.getCurrFrame().h > game.floorY) {
            game.assets->char0.setPosY(game.floorY - game.assets->char0.getCurrFrame().h);

        } else if (checkY < (game.roofY)) {
            game.assets->char0.setPosY(game.roofY);
            game.playerSpeed = 0;
        }

        const float alpha = accumulator / deltaTime; // %?

        game.window->clear();

        //prims loading
        game.window->drawRects(game.primRects);

        for (vector<Entity*>::iterator it = game.entities.begin(); it != game.entities.end(); ++it){
            game.window->render(*it);
        }

        bool passedObstacle = false;
        for (deque<Entity*>::iterator it = game.obstacles.begin(); it != game.obstacles.end(); ++it){
            if ((*it)->getPos().x + (*it)->getCurrFrame().w < 0) passedObstacle = true;
            (*it)->playIdleAnim(utils::timeInSeconds(), 0.1);
            game.window->render(*it);
        }
        if (passedObstacle) {
            Entity* freeThis = game.obstacles.front();
            game.obstacles.pop_front();
            delete freeThis;
        }

        game.window->display();

        int frameTicks = SDL_GetTicks() - startTicks; //ticks passed in this frame instance

        if (frameTicks < 1000 / game.window->getRefreshRate()){ //if too few ticks have passed, delay this frame
            SDL_Delay(1000 / game.window->getRefreshRate() - frameTicks);
        }
    }

    SDL_Quit();

    return 0;

}
