#include "Game.h"

Game::Game() : window(NULL), assets(NULL){
    window = new RenderWindow("Working Title Redone", *this);
    assets = new Assets(*this);

    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = width;
    windowRect.h = height;

    roofY = 90;
    floorY = height - roofY;

    playSpace.x = 0;
    playSpace.y = roofY;
    playSpace.w = width;
    playSpace.h = floorY - roofY;


    primRects.push_back(&windowRect);
    primRects.push_back(&playSpace);
}

void Game::restartRun(std::deque<Entity*>& obstacles) {
    std::cout << "Restarting" << std::endl;
    while (!obstacles.empty()) {
        Entity* freeThis = obstacles.front();
        obstacles.pop_front();
        delete freeThis;
    }
    gameSpeed = -5;
    gameOver = false;
    laserDelay = 1.5;
    timeSinceSpeedIncrease = utils::timeInSeconds();
    laserTime = utils::timeInSeconds();
}

Assets::Assets(Game& game) {
    SDL_Color red = { 255, 0, 0 };

    // TODO: set static variables for various classes with setter function (not implemented)
    //Texture* setWin = new Texture();
    //delete setWin;

    // ===========================================================
    // LOAD TEXTURES
    charTex.loadFromFile("res/img/charRight.png", game.window);

    testText.loadFromText("Game Title", red, 24, game.window);

    laserX1.loadFromFile("res/img/laserHorizontal1.png", game.window);
    laserX2.loadFromFile("res/img/laserHorizontal2.png", game.window);
    laserX3.loadFromFile("res/img/laserHorizontal3.png", game.window);

    laserY1.loadFromFile("res/img/laserVertical1.png", game.window);
    laserY2.loadFromFile("res/img/laserVertical2.png", game.window);
    laserY3.loadFromFile("res/img/laserVertical3.png", game.window);

    laserNegS1.loadFromFile("res/img/laserNegSlope1.png", game.window);
    laserNegS2.loadFromFile("res/img/laserNegSlope2.png", game.window);
    laserNegS3.loadFromFile("res/img/laserNegSlope3.png", game.window);

    laserPosS1.loadFromFile("res/img/laserPosSlope1.png", game.window);
    laserPosS2.loadFromFile("res/img/laserPosSlope2.png", game.window);
    laserPosS3.loadFromFile("res/img/laserPosSlope3.png", game.window);
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
    char0 = Character(Vector2f(game.width * 0.1, (float)game.height/2), &charTex);
    game.entities.push_back(&char0);

    screenMessage = Entity(Vector2f(50, 50), &testText);
    game.entities.push_back(&screenMessage);

    // END ENTITIES
    // ========================================================
}

