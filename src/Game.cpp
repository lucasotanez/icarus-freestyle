#include "Game.h"
#include "RenderWindow.h"

void Settings::restartRun(std::deque<Character*>& obstacles) {
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

// initialize game globals here
Settings game;
RenderWindow window = RenderWindow("Working Title", game.width, game.height);
