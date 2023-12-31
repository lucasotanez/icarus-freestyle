#ifndef GAME_H
#define GAME_H
#include <vector>
#include <deque>
#include "Utils.h"
#include "Character.h"
#include "RenderWindow.h"
#include "Texture.h"

struct Assets;

struct Game {
    public:
        Game();
        // game logic settings
        bool running = true;
        bool gameOver = true;
        bool gameOverUI = false;
        time_t timeSinceSpeedIncrease = utils::timeInSeconds();
        time_t laserTime = utils::timeInSeconds();
        float gameSpeed = 0;
        time_t timeSinceMove = utils::timeInSeconds();

        SDL_Event event;
        bool wPressed, sPressed, dPressed, aPressed, spacePressed, shiftPressed;

        // adjustable settings
        float playerSpeed = -5.5;
        float laserDelay = 1.5;
        float slideFactor = 0.02;
        int speedIncreaseDelay = 25;
        float speedIncreaseAmt = 0.2;

        int width = 1480;
        int height = 920;

        int roofY;
        int floorY;

        SDL_Rect playSpace;
        SDL_Rect floor;
        SDL_Rect roof;

        void restartRun(std::deque<Entity*>& obstacles); 

        void pollUserEvents();
        void logicRun(); // All core game logic
        void updateScreen();

        RenderWindow* window;
        Assets* assets;

        // All objects in these containers are shown on screen
        // Objects are rendered first to last (one in front of previous)
        std::deque<Entity*> background = {};
        std::vector<Entity*> entities = {};
        std::deque<Entity*> obstacles = {};
        std::vector<SDL_Rect*> primRects = {};
        std::vector<Entity*> ui = {};

        // Bookkeeping settings
        const float deltaTime = 0.01;
        float accumulator = 0.0;
        float currentTime = utils::timeInSeconds();

        int startTicks = -1; // ticks at the start of a frame

};

struct Assets {
    Assets(Game &game);
    Assets() {};

    // TEXTURES ===================================================
    Texture charTex, testText,
        laserX1, laserX2, laserX3,
        laserY1, laserY2, laserY3,
        laserNegS1, laserNegS2, laserNegS3,
        laserPosS1, laserPosS2, laserPosS3,
        charFlap1, charFlap2, charFlap3, charFlap4, charFlap5,
        charWalk1, charWalk2, charWalk3, charWalk4
    ;

    Texture sky0;

    // ANIMATIONS =================================================
    Animation
        laserIdleY, laserIdleX, laserIdleNS, laserIdlePS, icarusFlap, icarusWalk
    ;

    // ENTITIES ===================================================
    Character char0;

    Entity screenMessage;
    Entity backgroundImage;

};

#endif
