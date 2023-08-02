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

        void restartRun(std::deque<Character*>& obstacles); 

    private:

};

// include game globals
extern Settings game;
extern RenderWindow window;

#endif
