#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "RenderWindow.h"
#include "Entity.h"
#include "Utils.h"
#include "Character.h"

using namespace std;

int main(int argc, char* args[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) cout << "SDL_Init FAILED: " << SDL_GetError() << endl;
    if (!(IMG_Init(IMG_INIT_PNG))) cout << "IMG_Init FAILED: " << SDL_GetError() << endl;

    const int width = 1480;
    const int height = 920;

    RenderWindow window("Working Title", width, height);

    cout << "Refresh Rate: " << window.getRefreshRate() << endl;

    //===============================================================================
    //TEXTURES: Declare textures here (consider loading from file)
    //Ensure pathing to texture in res/img

    SDL_Texture* charRight = window.loadTexture("res/img/charRight.png");
    SDL_Texture* charLeft = window.loadTexture("res/img/charLeft.png");

    SDL_Texture* walkRight1 = window.loadTexture("res/img/charRightWalk1.png");
    SDL_Texture* walkRight2 = window.loadTexture("res/img/charRightWalk2.png");

    SDL_Texture* walkLeft1 = window.loadTexture("res/img/charLeftWalk1.png");
    SDL_Texture* walkLeft2 = window.loadTexture("res/img/charLeftWalk2.png");

    static SDL_Texture* laserX1 = window.loadTexture("res/img/laserHorizontal1.png");
    SDL_Texture* laserX2 = window.loadTexture("res/img/laserHorizontal2.png");
    SDL_Texture* laserX3 = window.loadTexture("res/img/laserHorizontal3.png");

    static SDL_Texture* laserY1 = window.loadTexture("res/img/laserVertical1.png");
    SDL_Texture* laserY2 = window.loadTexture("res/img/laserVertical2.png");
    SDL_Texture* laserY3 = window.loadTexture("res/img/laserVertical3.png");


    //END TEXTURES
    //===============================================================================

    //===============================================================================
    //ANIMATIONS: Declare animations here
    //1. Declare animation
    //2. Add frames

    Animation walkRightAnim;
    walkRightAnim.addFrame(walkRight1);
    walkRightAnim.addFrame(walkRight2);
    //walk right animation initialized
    Animation walkLeftAnim; walkLeftAnim.addFrame(walkLeft1);
    walkLeftAnim.addFrame(walkLeft2);
    //walk left animation initialized

    static Animation laserIdleY;
    laserIdleY.addFrame(laserY1);
    laserIdleY.addFrame(laserY2);
    laserIdleY.addFrame(laserY3);

    static Animation laserIdleX;
    laserIdleX.addFrame(laserX1);
    laserIdleX.addFrame(laserX2);
    laserIdleX.addFrame(laserX3);

    //END ANIMATIONS
    //===============================================================================

    Character char0(Vector2f(20, height/scaleF/2), charRight, 64, 64);


    //SERIALIZE ENTITIES HERE (for rendering)
    //=======================
    //first item in list is rendered first (behind all other items)
    vector<Entity*> entities = {&char0};
    deque<Character*> obstacles = {};

    //dynamic primitives
    vector<SDL_Rect*> primRects;

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 0;
    floor.w = width;
    floor.h = height;

    int roof_y, playHeight_y;
    roof_y = 20 * scaleF;
    playHeight_y = height - 2 * (20 * scaleF);

    SDL_Rect playSpace;
    playSpace.x = 0;
    playSpace.y = roof_y;
    playSpace.w = width;
    playSpace.h = playHeight_y;

    //constant primitives
    const vector<SDL_Rect*> constPrimRects = {&floor, &playSpace};

    //=======================

    bool gameRunning = true;

    SDL_Event event;

    const float deltaTime = 0.01;
    float accumulator = 0.0;
    float currentTime = utils::timeInSeconds();

    float playerSpeed = -2.5;
    float gameSpeed = -3;

    float spaceTime = utils::timeInSeconds();
    float upSpeed = 0;

    bool wPressed, sPressed, dPressed, aPressed, spacePressed, shiftPressed;
    wPressed = sPressed = dPressed = aPressed = spacePressed = shiftPressed = false;

    bool inAir = false;

    time_t laserTime = utils::timeInSeconds();


    class LaserVertical : public Character{
        public:
            LaserVertical(Vector2f p_pos)
            : Character(p_pos, laserY1, 32, 128, Hitbox(4, 8), &laserIdleY)
            {}
    };

    class LaserHorizontal : public Character {
        public:
            LaserHorizontal(Vector2f p_pos)
            : Character(p_pos, laserX1, 128, 32, Hitbox(8, 4), &laserIdleX)
            {}
    };

    class LaserNegativeSlope : public Character {
        public:
            // TODO: implement

    };

    class LaserPositiveSlope : public Character {
        public:
            // TODO: implement

    };

    //game loooooooop
    //IF GAME IS TAKING A LOT OF CPU: comment out all console logs

    while (gameRunning){

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
                    gameRunning = false;
                    cout << "Session time: [" << utils::timeInSeconds() << " seconds]" << endl;
                }
                if (event.type == SDL_KEYDOWN){
                    if (event.key.keysym.sym == SDLK_x){
                        gameRunning = false;
                    }
                    if (event.key.keysym.sym == SDLK_w){
                        wPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_a){
                        if (aPressed == false) {
                            char0.changeTex(charLeft);
                        }
                        aPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_d){
                        if (dPressed == false) {
                            char0.changeTex(charRight);
                        }
                        dPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        sPressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE && char0.getPos().y >= 100){
                        spacePressed = true;
                    }
                    if (event.key.keysym.sym == SDLK_r){
                        window.loadRect(primRects, char0.getPos().x * scaleF, char0.getPos().y * scaleF, 180, 150);
                    }
                    if (event.key.keysym.sym == SDLK_c){
                        primRects.clear();
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT && shiftPressed == false){
                        shiftPressed = true;
                        playerSpeed *= 2;
                    }
                }
                if (event.type == SDL_KEYUP){
                    if (event.key.keysym.sym == SDLK_w){
                        wPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_a){
                        if (dPressed == true) char0.changeTex(charRight);
                        else char0.changeTex(charLeft);
                        aPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_s){
                        sPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_d){
                        if (aPressed == true) char0.changeTex(charLeft);
                        else char0.changeTex(charRight);
                        dPressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE){
                        spacePressed = false;
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT){
                        shiftPressed = false;	
                        playerSpeed /= 2;
                    }
                }
            }
            //char0.getPos().print();
            //cout << playerSpeed << endl;
            //if (char0.collides(catBed)) cout << "collision detected" << endl;

            //cout << (char0.getPos().y) << " | " << (char0.getPos().y) << endl;
            
            float next_y = char0.getPos().y + playerSpeed;

            char0.movePos(0, playerSpeed);
            for (deque<Character*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
                (**it).movePos(gameSpeed, 0);
                if (char0.collides(**it)) {
                    cout << "collided with laser" << endl;
                }
            }
            accumulator -= deltaTime;
        }

        if (spacePressed){
            if (playerSpeed < 3.5) {
                playerSpeed += 0.15;
            }
            else playerSpeed = 3.5;
        }
        else {
            if (playerSpeed > -3.5) {
                playerSpeed -= 0.1;
            }
            else playerSpeed = -3.5;
        }

        if (utils::timeInSeconds() - laserTime >= 1.5) {
            int laserType = rand() % 2;
            Character* newEnt = nullptr;
            if (laserType == 0) newEnt = new LaserHorizontal(Vector2f((float)width/scaleF, rand() % (height / scaleF)));
            else if (laserType == 1) newEnt = new LaserVertical(Vector2f((float)width/scaleF, rand() % (height / scaleF)));
            obstacles.push_back(newEnt);
            laserTime = utils::timeInSeconds();
        }

        // bring out of bounds character back into scope BEFORE rendering:
        float checkY = char0.getPos().y;
        if (checkY + char0.getCurrFrame().h > (float)(playHeight_y + roof_y)/scaleF) {
            char0.setPosY((playHeight_y + roof_y)/scaleF - char0.getCurrFrame().h);

        } else if (checkY < ((float)roof_y/scaleF)) {
            char0.setPosY(roof_y/scaleF);
            playerSpeed = 0;
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
        for (deque<Character*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
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

