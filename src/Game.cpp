#include "Game.h"
#include "Lasers.h"

Game::Game() : window(NULL), assets(NULL) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) std::cout << "SDL_Init FAILED: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG_Init FAILED: " << SDL_GetError() << std::endl;
    if (TTF_Init() < 0) std::cout << TTF_GetError() << std::endl;

    window = new RenderWindow("Working Title Redone", *this);
    assets = new Assets(*this);

    roofY = 90;
    floorY = height - roofY;

    roof.x = 0;
    roof.y = 0;
    roof.h = roofY;
    roof.w = width;

    floor.x = 0;
    floor.y = floorY;
    floor.h = roofY;
    floor.w = width;

    playSpace.x = 0;
    playSpace.y = roofY;
    playSpace.w = width;
    playSpace.h = floorY - roofY;

    primRects.push_back(&playSpace);
    primRects.push_back(&floor);
    primRects.push_back(&roof);

    wPressed = sPressed = dPressed = aPressed = spacePressed = shiftPressed = false;
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
    gameOverUI = false;
}

void Game::pollUserEvents() {
    {
    // Technically the start of a frame, so this closure holds some bookkeeping
        startTicks = SDL_GetTicks();
        float newTime = utils::timeInSeconds();
        float frameTime = newTime - currentTime;
        if (frameTime > 0.25) frameTime = 0.25;
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= deltaTime) accumulator -= deltaTime;
    }

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_x) {
                running = false;
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
                if (gameOver == true) {
                    restartRun(obstacles);
                    ui.clear();
                }
            }
            if (event.key.keysym.sym == SDLK_SPACE && assets->char0.getPos().y >= 100){
                spacePressed = true;
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
}

void Game::logicRun() {
    if (!gameOver) {
        if (utils::timeInSeconds() - timeSinceSpeedIncrease > speedIncreaseDelay) {
            gameSpeed -= speedIncreaseAmt;
            timeSinceSpeedIncrease = utils::timeInSeconds();
        }
    }

    bool pushBackground = false;
    for (std::deque<Entity*>::iterator it = background.begin(); it != background.end(); ++it){
        (*it)->movePos(gameSpeed/4 - 0.4 , 0);
        if ((it + 1) == background.end()){
            if ((*it)->getPos().x <= 0) {
                pushBackground = true;
            }
        }
    }
    if (pushBackground) {
        background.push_back(new Entity(Vector2f(width, 0), &assets->sky0, Hitbox(0,0), NULL, 1));
    }

    assets->char0.movePos(playerSpeed);
    for (std::deque<Entity*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
        (*it)->movePos(gameSpeed, 0);
        if ((*it)->collides(assets->char0) && gameOver == false) {
            gameOver = true;
            std::cout << "collided with laser" << std::endl;
        }
    }

    if (spacePressed){
        if (!gameOver) {
            if (playerSpeed < 5.5) {
                playerSpeed += 0.4;
            }
            else playerSpeed = 5.5;
        }
    }
    else {
        if (playerSpeed > -5.5) {
            playerSpeed -= 0.4;
        }
        else playerSpeed = -5.5;
    }

    if (gameSpeed != 0){
        if (utils::timeInSeconds() - laserTime >= laserDelay) {
            int laserType = rand() % 4;
            Entity* newEnt = nullptr;
            int randY = playSpace.y + (rand() % ( playSpace.h - playSpace.y ));
            if (laserType == 0) newEnt = new LaserHorizontal(Vector2f((float)width, randY), assets);
            else if (laserType == 1) newEnt = new LaserVertical(Vector2f((float)width, randY), assets);
            else if (laserType == 2) newEnt = new LaserNegativeSlope(Vector2f((float)width, randY), assets);
            else if (laserType == 3) newEnt = new LaserPositiveSlope(Vector2f((float)width, randY), assets);
            obstacles.push_back(newEnt);
            laserTime = utils::timeInSeconds();
        }
    }

    if (gameOver) {
        spacePressed = false;
        if ( gameSpeed < 0 ) {
            gameSpeed += slideFactor;
        }
        else if ( gameSpeed > 0 ) {
            gameSpeed = 0;
            if (gameOverUI == false) {
                ui.push_back(&assets->screenMessage);
                gameOverUI = true;
            }
        }
    }

    // bring out of bounds character back into scope BEFORE rendering:
    float buf = float(assets->char0.getCurrFrame().h)/(assets->char0.getHitbox()->marginY);
    float checkY = assets->char0.getPos().y;
    if (checkY + assets->char0.getCurrFrame().h - buf > floorY) {
        assets->char0.setPosY(floorY - assets->char0.getCurrFrame().h + buf);

    } else if (checkY + buf < (roofY)) { assets->char0.setPosY(roofY - buf); playerSpeed = 0;
    }

    if (running == false) std::cout << "Session time: [" << utils::timeInSeconds() << " seconds]" << std::endl;
}

void Game::updateScreen() {
    window->clear();

    bool popBackground = false;
    for (std::deque<Entity*>::iterator it = background.begin(); it != background.end(); ++it){
        if ((*it)->getPos().x + (*it)->getCurrFrame().w < 0) popBackground = true;
        window->render(*it);
    }
    if (popBackground) {
        // bad free????
        //Entity* temp = background.front();
        background.pop_front();
        //delete temp;
    }

    window->drawRects(primRects);

    for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
        if (entities[0]->getPos().x > floorY - 5) entities[0]->playRunAnim(utils::timeInSeconds(), 0.1);
        else entities[0]->playIdleAnim(utils::timeInSeconds(), 0.1);
        window->render(*it);
    }

    bool passedObstacle = false;
    for (std::deque<Entity*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it){
        if ((*it)->getPos().x + (*it)->getCurrFrame().w < 0) passedObstacle = true;
        (*it)->playIdleAnim(utils::timeInSeconds(), 0.1);
        window->render(*it);
    }
    if (passedObstacle) {
        Entity* freeThis = obstacles.front();
        obstacles.pop_front();
        delete freeThis;
    }

    for (std::vector<Entity*>::iterator it = ui.begin(); it != ui.end(); ++it) {
        window->render(*it);
    }

    window->display();

    {
    // Technically the end of a frame, so this closure holds bookkeeping code
    // IMPORTANT performance maintaining code
        // const float alpha = accumulator / deltaTime; // %
        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < 1000 / window->getRefreshRate()) {
            // If too few ticks have passed, delay this frame
            SDL_Delay(1000 / window->getRefreshRate() - frameTicks);
        }
    }

}

Assets::Assets(Game& game) {
    SDL_Color red = { 255, 0, 0 };

    // TODO: set static variables for various classes with setter function (not implemented)

    // ===========================================================
    // LOAD TEXTURES
    charTex.loadFromFile("res/img/icarus0.png", game.window);
    charFlap1.loadFromFile("res/img/icarus1.png", game.window);
    charFlap2.loadFromFile("res/img/icarus2.png", game.window);
    charFlap3.loadFromFile("res/img/icarus3.png", game.window);
    charFlap4.loadFromFile("res/img/icarus4.png", game.window);
    charFlap5.loadFromFile("res/img/icarus5.png", game.window);

    charWalk1.loadFromFile("res/img/icarusWalk1.png", game.window);
    charWalk2.loadFromFile("res/img/icarusWalk2.png", game.window);
    charWalk3.loadFromFile("res/img/icarusWalk3.png", game.window);
    charWalk4.loadFromFile("res/img/icarusWalk4.png", game.window);

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

    sky0.loadFromFile("res/img/sky.png", game.window);
    sky0.background(&game);
    // END TEXTURES
    // =========================================================

    // =========================================================
    // LOAD ANIMATIONS
    icarusFlap.addFrame(&charTex);
    icarusFlap.addFrame(&charFlap1);
    icarusFlap.addFrame(&charFlap3);
    icarusFlap.addFrame(&charFlap1);
    icarusFlap.addFrame(&charTex);
    icarusFlap.addFrame(&charFlap2);
    icarusFlap.addFrame(&charFlap4);
    icarusFlap.addFrame(&charFlap2);

    icarusWalk.addFrame(&charWalk1);
    icarusWalk.addFrame(&charWalk2);
    icarusWalk.addFrame(&charWalk3);
    icarusWalk.addFrame(&charWalk4);

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
    backgroundImage = Entity(Vector2f(0,0), &sky0, Hitbox(0,0), NULL, 1);
    game.background.push_back(&backgroundImage);
    char0 = Character(Vector2f(game.width * 0.1, (float)game.height/2), &charTex, Hitbox(4, 4), &icarusFlap, &icarusWalk);
    game.entities.push_back(&char0);

    screenMessage = Entity(Vector2f(50, 50), &testText);

    // END ENTITIES
    // ========================================================
}
