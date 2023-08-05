#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include <vector>

struct Game;

class RenderWindow{
    public:
        RenderWindow(const char* p_title, Game& game);
        RenderWindow();
        ~RenderWindow();
        SDL_Texture* loadTexture(const char* p_filePath);
        SDL_Texture* loadTextureFromString(const char* message, int size, SDL_Color color);

        int getRefreshRate();

        void clear();
        void render(Entity* ent);
        void display();

        void loadRect(std::vector<SDL_Rect*> &prims, int x, int y, int w, int h);
        const void drawRects(std::vector<SDL_Rect*> &prims);

        inline SDL_Renderer* getRenderer() { return renderer; };
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif
