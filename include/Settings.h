#ifndef SETTINGS_H
#define SETTINGS_H
#include "Utils.h"

struct Settings {
    public:
        bool running = true;
        bool gameOver = false;

        float playerSpeed = -2.5;
        float gameSpeed = -3;
        float laserDelay = 1.5;
        float slideFactor = 0.01;
        int speedIncreaseDelay = 25;
        float speedIncreaseAmt = 0.2;
        time_t timeSinceSpeedIncrease = utils::timeInSeconds();
        time_t laserTime = utils::timeInSeconds();

};

#endif
