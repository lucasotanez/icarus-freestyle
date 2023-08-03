#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "Entity.h"
#include "Utils.h"
#include "Character.h"
#include "Game.h"
#include "Lasers.h"

using namespace std;

int main(int argc, char* args[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) cout << "SDL_Init FAILED: " << SDL_GetError() << endl;
    if (!(IMG_Init(IMG_INIT_PNG))) cout << "IMG_Init FAILED: " << SDL_GetError() << endl;
    if (TTF_Init() < 0) cout << TTF_GetError() << endl;

    cout << "Refresh Rate: " << window.getRefreshRate() << endl;

    //===============================================================================
    //===============================================================================
    //first item in list is rendered first (behind all other items)
    vector<Entity*> entities = {&assets.char0, &assets.screenMessage};
    deque<Entity*> obstacles = {};

    //dynamic primitives
    vector<SDL_Rect*> primRects;

    SDL_Rect bgVoid;
    bgVoid.x = 0;
    bgVoid.y = 0;
    bgVoid.w = game.width;
    bgVoid.h = game.height;

    int roof_y, playHeight_y;
    roof_y = 20 * scaleF;
    playHeight_y = game.height - 2 * (20 * scaleF);

    SDL_Rect playSpace;
    playSpace.x = 0;
    playSpace.y = roof_y;
    playSpace.w = game.width;
    playSpace.h = playHeight_y;

    //constant primitives
    const vector<SDL_Rect*> constPrimRects = {&bgVoid, &playSpace};

    //=======================

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
                        if (game.gameOver == true) game.restartRun(obstacles);
                    }
                    if (event.key.keysym.sym == SDLK_SPACE && assets.char0.getPos().y >= 100){
                        spacePressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_r){
                        window.loadRect(primRects, assets.char0.getPos().x * scaleF, assets.char0.getPos().y * scaleF, 180, 150);
                    }
                    if (event.key.keysym.sym == SDLK_c){
                        primRects.clear();
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
            //char0.getPos().print();
            //cout << playerSpeed << endl;
            //if (char0.collides(catBed)) cout << "collision detected" << endl;


            accumulator -= deltaTime;
        }

        if (!game.gameOver) {
            if (utils::timeInSeconds() - game.timeSinceSpeedIncrease > game.speedIncreaseDelay) {
                game.gameSpeed -= game.speedIncreaseAmt;
                game.timeSinceSpeedIncrease = utils::timeInSeconds();
            }
        }

        assets.char0.movePos(game.playerSpeed);
        for (deque<Entity*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
            (**it).movePos(game.gameSpeed, 0);
            if ((*it)->collides(assets.char0) && game.gameOver == false) {
                game.gameOver = true;
                cout << "collided with laser" << endl;
            }
        }

        if (spacePressed){
            if (!game.gameOver) {
                if (game.playerSpeed < 2.5) {
                    game.playerSpeed += 0.15;
                }
                else game.playerSpeed = 2.5;
            }
        }
        else {
            if (game.playerSpeed > -2.5) {
                game.playerSpeed -= 0.1;
            }
            else game.playerSpeed = -2.5;
        }

        if (game.gameSpeed != 0){
            if (utils::timeInSeconds() - game.laserTime >= game.laserDelay) {
                int laserType = rand() % 4;
                Entity* newEnt = nullptr;
                if (laserType == 0) newEnt = new LaserHorizontal(Vector2f((float)game.width/scaleF, rand() % (game.height / scaleF - 80)));
                else if (laserType == 1) newEnt = new LaserVertical(Vector2f((float)game.width/scaleF, rand() % (game.height / scaleF - 80)));
                else if (laserType == 2) newEnt = new LaserNegativeSlope(Vector2f((float)game.width/scaleF, rand() % (game.height / scaleF - 80)));
                else if (laserType == 3) newEnt = new LaserPositiveSlope(Vector2f((float)game.width/scaleF, rand() % (game.height / scaleF - 80)));
                obstacles.push_back(newEnt);
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
        float checkY = assets.char0.getPos().y;
        if (checkY + assets.char0.getCurrFrame().h > (float)(playHeight_y + roof_y)/scaleF) {
            assets.char0.setPosY((playHeight_y + roof_y)/scaleF - assets.char0.getCurrFrame().h);

        } else if (checkY < ((float)roof_y/scaleF)) {
            assets.char0.setPosY(roof_y/scaleF);
            game.playerSpeed = 0;
        }

        const float alpha = accumulator / deltaTime; // %?

        window.clear();

        //prims loading
        window.drawRects(constPrimRects);
        window.drawRects(primRects);

        for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it){
            window.render(**it);
        }

        bool passedObstacle = false;
        for (deque<Entity*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
            if ((*it)->getPos().x + (*it)->getCurrFrame().w < 0) passedObstacle = true;
            (*it)->playIdleAnim(utils::timeInSeconds(), 0.1);
            window.render(**it);
        }
        if (passedObstacle) {
            Entity* freeThis = obstacles.front();
            obstacles.pop_front();
            delete freeThis;
        }

        window.display();

        int frameTicks = SDL_GetTicks() - startTicks; //ticks passed in this frame instance

        if (frameTicks < 1000 / window.getRefreshRate()){ //if too few ticks have passed, delay this frame
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    SDL_Quit();

    return 0;

}
