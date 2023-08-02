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
#include "Texture.h"

using namespace std;

int main(int argc, char* args[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) cout << "SDL_Init FAILED: " << SDL_GetError() << endl;
    if (!(IMG_Init(IMG_INIT_PNG))) cout << "IMG_Init FAILED: " << SDL_GetError() << endl;
    if (TTF_Init() < 0) cout << TTF_GetError() << endl;

    cout << "Refresh Rate: " << window.getRefreshRate() << endl;

    //===============================================================================
    //TEXTURES: Declare textures here (consider loading from file)
    //Ensure pathing to texture in res/img

    Texture charRight;
    charRight.loadFromFile("res/img/charRight.png");


    //SDL_Texture* charRight = window.loadTexture("res/img/charRight.png");
    //SDL_Texture* charLeft = window.loadTexture("res/img/charLeft.png");

    //SDL_Texture* walkRight1 = window.loadTexture("res/img/charRightWalk1.png");
    SDL_Texture* walkRight2 = window.loadTexture("res/img/charRightWalk2.png");

    //SDL_Texture* walkLeft1 = window.loadTexture("res/img/charLeftWalk1.png");
    SDL_Texture* walkLeft2 = window.loadTexture("res/img/charLeftWalk2.png");

    //static SDL_Texture* laserX1 = window.loadTexture("res/img/laserHorizontal1.png");
    SDL_Texture* laserX2 = window.loadTexture("res/img/laserHorizontal2.png");
    SDL_Texture* laserX3 = window.loadTexture("res/img/laserHorizontal3.png");

    //static SDL_Texture* laserY1 = window.loadTexture("res/img/laserVertical1.png");
    SDL_Texture* laserY2 = window.loadTexture("res/img/laserVertical2.png");
    SDL_Texture* laserY3 = window.loadTexture("res/img/laserVertical3.png");

    //static SDL_Texture* laserNegS1 = window.loadTexture("res/img/laserNegSlope1.png");
    SDL_Texture* laserNegS2 = window.loadTexture("res/img/laserNegSlope2.png");
    SDL_Texture* laserNegS3 = window.loadTexture("res/img/laserNegSlope3.png");
    
    //static SDL_Texture* laserPosS1 = window.loadTexture("res/img/laserPosSlope1.png");
    SDL_Texture* laserPosS2 = window.loadTexture("res/img/laserPosSlope2.png");
    SDL_Texture* laserPosS3 = window.loadTexture("res/img/laserPosSlope3.png");

    SDL_Color red = { 255, 0, 0 };
    //SDL_Texture* testText = window.loadTextureFromString("Game Title", 24, red);
    Texture testText; testText.loadFromText("Game Title", red, 24);

    static Texture laserX1; laserX1.loadFromFile("res/img/laserHorizontal1.png");
    //Texture laserX2; laserX1.loadFromFile("res/img/laserHorizontal2.png");
    //Texture laserX3; laserX1.loadFromFile("res/img/laserHorizontal3.png");

    static Texture laserY1; laserY1.loadFromFile("res/img/laserVertical1.png");
    //Texture laserY2; laserX1.loadFromFile("res/img/laserVertical2.png");
    //Texture laserY3; laserX1.loadFromFile("res/img/laserVertical3.png");

    static Texture laserNegS1; laserNegS1.loadFromFile("res/img/laserNegSlope1.png");
    //Texture laserNegS2; laserX1.loadFromFile("res/img/laserNegSlope2.png");
    //Texture laserNegS3; laserX1.loadFromFile("res/img/laserNegSlope3.png");

    static Texture laserPosS1; laserPosS1.loadFromFile("res/img/laserPosSlope1.png");
    //Texture laserPosS2; laserX1.loadFromFile("res/img/laserPosSlope2.png");
    //Texture laserPosS3; laserX1.loadFromFile("res/img/laserPosSlope3.png");

    //END TEXTURES
    //===============================================================================

    //===============================================================================
    //ANIMATIONS: Declare animations here
    //1. Declare animation
    //2. Add frames

    //Animation walkRightAnim;
    //walkRightAnim.addFrame(walkRight1);
    //walkRightAnim.addFrame(walkRight2);
    //walk right animation initialized
    //Animation walkLeftAnim; walkLeftAnim.addFrame(walkLeft1);
    //walkLeftAnim.addFrame(walkLeft2);
    //walk left animation initialized

    //static Animation laserIdleY;
    //laserIdleY.addFrame(laserY1);
    //laserIdleY.addFrame(laserY2);
    //laserIdleY.addFrame(laserY3);

    //static Animation laserIdleX;
    //laserIdleX.addFrame(laserX1);
    //laserIdleX.addFrame(laserX2);
    //laserIdleX.addFrame(laserX3);
    //
    //static Animation laserIdleNS;
    //laserIdleNS.addFrame(laserNegS1);
    //laserIdleNS.addFrame(laserNegS2);
    //laserIdleNS.addFrame(laserNegS3);
    //
    //static Animation laserIdlePS;
    //laserIdlePS.addFrame(laserPosS1);
    //laserIdlePS.addFrame(laserPosS2);
    //laserIdlePS.addFrame(laserPosS3);

    //END ANIMATIONS
    //===============================================================================

    Character char0(Vector2f(20, game.height/scaleF/2), &charRight);
    Character screenMessage(Vector2f(50, 50), &testText);


    //SERIALIZE ENTITIES HERE (for rendering)
    //===============================================================================
    //first item in list is rendered first (behind all other items)
    vector<Entity*> entities = {&char0, &screenMessage};
    deque<Character*> obstacles = {};

    //dynamic primitives
    vector<SDL_Rect*> primRects;

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 0;
    floor.w = game.width;
    floor.h = game.height;

    int roof_y, playHeight_y;
    roof_y = 20 * scaleF;
    playHeight_y = game.height - 2 * (20 * scaleF);

    SDL_Rect playSpace;
    playSpace.x = 0;
    playSpace.y = roof_y;
    playSpace.w = game.width;
    playSpace.h = playHeight_y;

    //constant primitives
    const vector<SDL_Rect*> constPrimRects = {&floor, &playSpace};

    //=======================

    SDL_Event event;

    const float deltaTime = 0.01;
    float accumulator = 0.0;
    float currentTime = utils::timeInSeconds();

    bool wPressed, sPressed, dPressed, aPressed, spacePressed, shiftPressed;
    wPressed = sPressed = dPressed = aPressed = spacePressed = shiftPressed = false;

    class LaserVertical : public Character{
        public:
            LaserVertical(Vector2f p_pos)
            //: Character(p_pos, laserY1, 32, 128, Hitbox(4, 8), &laserIdleY)
            : Character(p_pos, &laserY1, Hitbox(4, 8))
            {}
    };

    class LaserHorizontal : public Character {
        public:
            LaserHorizontal(Vector2f p_pos)
            //: Character(p_pos, laserX1, 128, 32, Hitbox(8, 4), &laserIdleX)
            : Character(p_pos, &laserX1, Hitbox(8, 4))
            {}
    };

    class LaserNegativeSlope : public Character {
        public:
            LaserNegativeSlope(Vector2f p_pos)
            //: Character(p_pos, laserNegS1, 128, 128, Hitbox(8, 8), &laserIdleNS)
            : Character(p_pos, &laserNegS1, Hitbox(8, 8))
            {}

            bool collides(const Entity &ent) const override {
                //// hitbox dimensions should be square for this class of laser
                if (ent.getHitbox().marginX != ent.getHitbox().marginY) return false;

                // hitbox buffers
                float entLeft = ent.getPos().x + ((float)ent.getCurrFrame().w/ent.getHitbox().marginX);
                float entRight = ent.getPos().x + ent.getCurrFrame().w - ((float)ent.getCurrFrame().w/ent.getHitbox().marginX);
                float entTop = ent.getPos().y + ((float)ent.getCurrFrame().h/ent.getHitbox().marginY);
                float entBot = ent.getPos().y + ent.getCurrFrame().h - ((float)ent.getCurrFrame().h/ent.getHitbox().marginY);

                float thisLeft = this->getPos().x + (float)this->getCurrFrame().w/this->getHitbox().marginX;
                float thisRight = this->getPos().x + this->getCurrFrame().w - (float)this->getCurrFrame().w/this->getHitbox().marginX;
                float thisBot = this->getPos().y + this->getCurrFrame().h - (float)this->getCurrFrame().h/this->getHitbox().marginY;
                float thisTop = this->getPos().y + (float)this->getCurrFrame().h/this->getHitbox().marginY;

                if (thisLeft > entRight || thisRight < entLeft) return false;
                if (thisTop > entBot || thisBot < entTop) return false;
                int vertScale = this->getCurrFrame().w - (this->getCurrFrame().w + thisLeft - entLeft);
                int passingY = thisTop + vertScale;
                if (passingY > entTop && passingY < entBot){
                    return true;
                } else return false;
            }

    };

    class LaserPositiveSlope : public Character {
        public:
            LaserPositiveSlope(Vector2f p_pos)
            //: Character(p_pos, laserPosS1, 128, 128, Hitbox(8, 8), &laserIdlePS)
            : Character(p_pos, &laserPosS1, Hitbox(8, 8))
            {}

            bool collides(const Entity &ent) const override {
                //// hitbox dimensions should be square for this class of laser
                if (ent.getHitbox().marginX != ent.getHitbox().marginY) return false;

                // hitbox buffers
                float entLeft = ent.getPos().x + ((float)ent.getCurrFrame().w/ent.getHitbox().marginX);
                float entRight = ent.getPos().x + ent.getCurrFrame().w - ((float)ent.getCurrFrame().w/ent.getHitbox().marginX);
                float entTop = ent.getPos().y + ((float)ent.getCurrFrame().h/ent.getHitbox().marginY);
                float entBot = ent.getPos().y + ent.getCurrFrame().h - ((float)ent.getCurrFrame().h/ent.getHitbox().marginY);

                float thisLeft = this->getPos().x + (float)this->getCurrFrame().w/this->getHitbox().marginX;
                float thisRight = this->getPos().x + this->getCurrFrame().w - (float)this->getCurrFrame().w/this->getHitbox().marginX;
                float thisBot = this->getPos().y + this->getCurrFrame().h - (float)this->getCurrFrame().h/this->getHitbox().marginY;
                float thisTop = this->getPos().y + (float)this->getCurrFrame().h/this->getHitbox().marginY;

                if (thisLeft > entRight || thisRight < entLeft) return false;
                if (thisTop > entBot || thisBot < entTop) return false;
                int vertScale = this->getCurrFrame().w - (this->getCurrFrame().w + thisLeft - entLeft);
                int passingY = thisBot - vertScale;
                if (passingY > entTop && passingY < entBot){
                    return true;
                } else return false;
            }

    };

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

        char0.movePos(0, game.playerSpeed);
        for (deque<Character*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
            (**it).movePos(game.gameSpeed, 0);
            if ((*it)->collides(char0) && game.gameOver == false) {
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
                Character* newEnt = nullptr;
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
        float checkY = char0.getPos().y;
        if (checkY + char0.getCurrFrame().h > (float)(playHeight_y + roof_y)/scaleF) {
            char0.setPosY((playHeight_y + roof_y)/scaleF - char0.getCurrFrame().h);

        } else if (checkY < ((float)roof_y/scaleF)) {
            char0.setPosY(roof_y/scaleF);
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
        for (deque<Character*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
            if ((*it)->getPos().x + (*it)->getCurrFrame().w < 0) passedObstacle = true;
            //(*it)->playIdleAnim(utils::timeInSeconds(), 0.1);
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
