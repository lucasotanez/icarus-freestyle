#include "Texture.h"
#include <iostream>
#include "Game.h"


Texture::Texture()
: _texture(NULL), _width(0), _height(0)
{}

Texture::~Texture()
{
    // get rid of existing texture
    free();
}

bool Texture::loadFromFile(const char* path )
{
    //free();
    //SDL_Texture* newTexture = NULL;
    //SDL_Surface* loadedSurface = IMG_Load(path);
    //if (loadedSurface == NULL){
    //    std::cout << "Unable to load image: " << IMG_GetError() << std::endl;
    //}
    //else {
    //    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

    //    newTexture = SDL_CreateTextureFromSurface( window.getRenderer(), loadedSurface );
    //    if ( newTexture == NULL ) {
    //        std::cout << "Unable to create texture: " << SDL_GetError() << std::endl;
    //    }
    //    else {
    //        _width = loadedSurface->w;
    //        _height = loadedSurface->h;
    //    }

    //    SDL_FreeSurface( loadedSurface );
    //}

    //_texture = newTexture;
    //return _texture != NULL;
    return true;
}

//TODO: load textures into renderer
//TODO: delete will-be-redundant code in main loop
//TODO: get access to window renderer in a better way (constructor to data member?) 
//TODO: change entity constructor to not accept dimensions, as dimensions are instead
//      data members of this new "Texture" class.

bool Texture::loadFromText(const char* text, SDL_Color color, int size)
{
    //free();
    //TTF_Font* font = TTF_OpenFont( "res/fonts/slkscr.ttf", size );
    //if ( font == NULL ){
    //    std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    //    return false;
    //}
    //SDL_Surface* messageSurface = TTF_RenderText_Solid(font, text, color);
    //if ( messageSurface == NULL ) {
    //    std::cout << "Unable to render surface" << TTF_GetError() << std::endl;
    //    return false;
    //}
    //SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), messageSurface);
    //_texture = texture;
    return true;
}

void Texture::free()
{
    if ( _texture != NULL ) {
        SDL_DestroyTexture( _texture );
        _texture = NULL;
        _width = 0;
        _height = 0;
    }
}
