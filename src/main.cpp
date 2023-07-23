#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
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

    SDL_Texture* kittyBed = window.loadTexture("res/img/kittybed/kittybed.png");
    SDL_Texture* kittyBedFilled = window.loadTexture("res/img/kittybed/kittybedfilled.png");


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
    Animation walkLeftAnim;
    walkLeftAnim.addFrame(walkLeft1);
    walkLeftAnim.addFrame(walkLeft2);
    //walk left animation initialized

    //END ANIMATIONS
    //===============================================================================

    Character char0(Vector2f(100, 60), charRight, 64, 64, walkRightAnim, walkLeftAnim);

    Entity catBed(Vector2f(240, 30), kittyBed, 64, 64);


    //SERIALIZE ENTITIES HERE (for rendering)
    //=======================
    //first item in list is rendered first (behind all other items)
    vector<Entity*> entities = {&catBed, &char0};

    //dynamic primitives
    vector<SDL_Rect*> primRects;

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 0;
    floor.w = width;
    floor.h = height;

    //constant primitives
    const vector<SDL_Rect*> constPrimRects = {&floor};

    //=======================

    bool gameRunning = true;

    SDL_Event event;

    const float deltaTime = 0.01;
    float accumulator = 0.0;
    float currentTime = utils::timeInSeconds();

    float playerSpeed = 1;

    float spaceTime = utils::timeInSeconds();
    float upSpeed = 0;

    bool wPressed, sPressed, dPressed, aPressed, spacePressed, shiftPressed;
    wPressed = sPressed = dPressed = aPressed = spacePressed = shiftPressed = false;

    bool inAir = false;

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
            if (char0.collides(catBed)) cout << "collision detected" << endl;

            if (char0.getPos().y >= 0 && char0.getPos().y <= height/scaleF - 64/*height/4*/){
                if (wPressed){
                    char0.movePos(playerSpeed, 'N');
                }
                if (sPressed){
                    char0.movePos(playerSpeed, 'S');
                }
            }
            if (char0.getPos().x >= 0 && char0.getPos().x <= width/scaleF - 64){
                if (aPressed && dPressed){} //Do nothing
                else if (aPressed){
                    char0.movePos(playerSpeed, 'W');
                    char0.playAnimation(&walkLeftAnim, utils::timeInSeconds(), 0.25);
                }
                else if (dPressed){
                    char0.movePos(playerSpeed, 'E');
                    char0.playAnimation(&walkRightAnim, utils::timeInSeconds(), 0.25);
                }
            }
            if (char0.getPos().x > width/scaleF - 64){
                char0.setPos(width/scaleF - 64, char0.getPos().y);
            }
            if (char0.getPos().x < 0){
                char0.setPos(0, char0.getPos().y);
            }
            if (char0.getPos().y > static_cast<float>(height)/scaleF - 64){
                char0.setPos(char0.getPos().x, height/scaleF - 64);
            }
            if (char0.getPos().y < 0){
                char0.setPos(char0.getPos().x, 0);
   	        }
            accumulator -= deltaTime;
        }

        const float alpha = accumulator / deltaTime; // %?

        window.clear();

        //prims loading
        window.drawRects(constPrimRects);
        window.drawRects(primRects);

        for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it){
            window.render(**it);
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
