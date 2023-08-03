#ifndef GAME_H
#define GAME_H
#include <deque>
#include "Utils.h"
#include "Character.h"
#include "RenderWindow.h"

struct Settings {
    public:
        // game logic settings
        bool running = true;
        bool gameOver = true;
        time_t timeSinceSpeedIncrease = utils::timeInSeconds();
        time_t laserTime = utils::timeInSeconds();
        float gameSpeed = 0;

        // adjustable settings
        float playerSpeed = -2.5;
        float laserDelay = 1.5;
        float slideFactor = 0.01;
        int speedIncreaseDelay = 25;
        float speedIncreaseAmt = 0.2;

        int width = 1480;
        int height = 920;

        void restartRun(std::deque<Entity*>& obstacles); 

    private:

};

struct Assets {
    Assets(Settings &game);

    // TEXTURES ===================================================
    Texture charTex, testText,
        laserX1, laserX2, laserX3,
        laserY1, laserY2, laserY3,
        laserNegS1, laserNegS2, laserNegS3,
        laserPosS1, laserPosS2, laserPosS3
    ;

    // ANIMATIONS =================================================
    Animation
        laserIdleY, laserIdleX, laserIdleNS, laserIdlePS
    ;


    // ENTITIES ===================================================
    Character char0;

    Entity screenMessage;
    


};

// include game globals ( initialized in main.cpp )
extern Settings game;
extern RenderWindow window;
extern Assets assets;


#endif
