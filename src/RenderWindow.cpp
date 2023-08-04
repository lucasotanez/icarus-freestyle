#include "RenderWindow.h"
#include "Entity.h"
#include <iostream>
#include "Game.h"

using namespace std;

RenderWindow::RenderWindow(const char* p_title, Game& game)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.width, game.height, SDL_WINDOW_SHOWN);

    if (window == NULL){
        cout << "Window failed to load" << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

RenderWindow::RenderWindow() 
    : window(NULL), renderer(NULL)
{}

RenderWindow::~RenderWindow(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL){
        cout << "Failed to load texture: " << SDL_GetError() << endl;
    }
    return texture;
}

SDL_Texture* RenderWindow::loadTextureFromString(const char* message, int size, SDL_Color color){
    TTF_Font* font = TTF_OpenFont( "res/fonts/slkscr.ttf", 28 );
    if ( font == NULL ){
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message, color);
    if ( messageSurface == NULL ) {
        std::cout << "Unable to render surface" << TTF_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    return texture;
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}


void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}


void RenderWindow::render(Entity& ent){

    SDL_Rect src;
    src.x = ent.getCurrFrame().x;
    src.y = ent.getCurrFrame().y;
    src.w = ent.getCurrFrame().w;
    src.h = ent.getCurrFrame().h;

    SDL_Rect dst;
    dst.x = ent.getPos().x * scaleF;
    dst.y = ent.getPos().y * scaleF;
    dst.w = ent.getCurrFrame().w * scaleF;
    dst.h = ent.getCurrFrame().h * scaleF;

    SDL_RenderCopy(renderer, ent.getTex()->getTex(), &src, &dst);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

void RenderWindow::loadRect(vector<SDL_Rect*> &prims, int x, int y, int w, int h){
    SDL_Rect* rect = new SDL_Rect;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    prims.push_back(rect);
}


const void RenderWindow::drawRects(vector<SDL_Rect*> &prims){
    SDL_SetRenderDrawColor(renderer, 0, 255, 200, 255);
    for (int i = 0; i < prims.size(); i++){
        SDL_RenderDrawRect(renderer, prims[i]);
        SDL_RenderFillRect(renderer, prims[i]);
    }

}

const void RenderWindow::drawRects(const vector<SDL_Rect*> &prims){
    for (int i = 0; i < prims.size(); i++){
        if (i == 0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, prims[i]);
        }
        else if (i == 1) SDL_SetRenderDrawColor(renderer, 150, 150, 150, 150);
        SDL_RenderDrawRect(renderer, prims[i]);
    }
}
