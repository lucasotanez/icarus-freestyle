#ifndef SETTINGS_H
#define SETTINGS_H
#include <deque>
#include "Utils.h"
#include "Character.h"

struct Settings {
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

    void restartRun(std::deque<Character*>& obstacles){
        std::cout << "Restarting" << std::endl;
        while (!obstacles.empty()) {
            Entity* freeThis = obstacles.front();
            obstacles.pop_front();
            delete freeThis;
        }
        gameSpeed = -2;
        gameOver = false;
        laserDelay = 1.5;
        timeSinceSpeedIncrease = utils::timeInSeconds();
        laserTime = utils::timeInSeconds();
    }

};

#endif
