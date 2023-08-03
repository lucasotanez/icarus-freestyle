#include "Game.h"

void Settings::restartRun(std::deque<Entity*>& obstacles) {
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

Assets::Assets(Settings &game) {
    SDL_Color red = { 255, 0, 0 };

    // ===========================================================
    // LOAD TEXTURES
    charTex.loadFromFile("res/img/charRight.png");

    testText.loadFromText("Game Title", red, 24);

    laserX1.loadFromFile("res/img/laserHorizontal1.png");
    laserX2.loadFromFile("res/img/laserHorizontal2.png");
    laserX3.loadFromFile("res/img/laserHorizontal3.png");

    laserY1.loadFromFile("res/img/laserVertical1.png");
    laserY2.loadFromFile("res/img/laserVertical2.png");
    laserY3.loadFromFile("res/img/laserVertical3.png");

    laserNegS1.loadFromFile("res/img/laserNegSlope1.png");
    laserNegS2.loadFromFile("res/img/laserNegSlope2.png");
    laserNegS3.loadFromFile("res/img/laserNegSlope3.png");

    laserPosS1.loadFromFile("res/img/laserPosSlope1.png");
    laserPosS2.loadFromFile("res/img/laserPosSlope2.png");
    laserPosS3.loadFromFile("res/img/laserPosSlope3.png");
    // END TEXTURES
    // =========================================================

    // =========================================================
    // LOAD ANIMATIONS
    laserIdleY.addFrame(&laserY1);
    laserIdleY.addFrame(&laserY2);
    laserIdleY.addFrame(&laserY3);

    laserIdleX.addFrame(&laserX1);
    laserIdleX.addFrame(&laserX2);
    laserIdleX.addFrame(&laserX3);
    
    laserIdleNS.addFrame(&laserNegS1);
    laserIdleNS.addFrame(&laserNegS2);
    laserIdleNS.addFrame(&laserNegS3);
    
    laserIdlePS.addFrame(&laserPosS1);
    laserIdlePS.addFrame(&laserPosS2);
    laserIdlePS.addFrame(&laserPosS3);
    // END ANIMATIONS
    // ========================================================

    // ========================================================
    // LOAD ENTITIES
    //char0.changeTex(&charTex);
    //char0.setPos(Vector2f(20, (float)game.height/scaleF/2));
    char0 = Character(Vector2f(20, (float)game.height/scaleF/2), &charTex);

    screenMessage = Entity(Vector2f(50, 50), &testText);
    // END ENTITIES
    // ========================================================
}

Settings game;
RenderWindow window = RenderWindow("Working Title", game.width, game.height);
Assets assets(game);

