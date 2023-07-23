#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include <vector>

const uint8_t scaleF = 4;

class RenderWindow{
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        ~RenderWindow();
        SDL_Texture* loadTexture(const char* p_filePath);

        int getRefreshRate();

        void clear();
        void render(Entity& ent);
        void display();

        void loadRect(std::vector<SDL_Rect*> &prims, int x, int y, int w, int h);
        const void drawRects(std::vector<SDL_Rect*> &prims);
        const void drawRects(const std::vector<SDL_Rect*> &prims);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif