#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_error.h>
#include <string>
using namespace std;

typedef unsigned int uint;

class Texture {
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height
    uint numCols = 1;
    uint numRows = 1;

public:
    // Constructors
    Texture(SDL_Renderer* r) : renderer(r) {};
    Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1);
    // Destructor
    ~Texture() { _free(); };
    // Destroys the texture
    void _free();
    // Returns the width of the texture
    int getW() const { return w; };
    // Returns the height of the texture
    int getH() const { return h; };
    // Returns the number of columns
    uint getNumCols() const { return numCols; };
    // Returns the texture pointer
    SDL_Texture* getTexture() const { return texture; };
    // Loads a texture from the specified
    void load(string filename, uint numRows = 1, uint numCols = 1);
    // Draws single texture on screen
    void render(const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    // Draws texture depending of the frame we want from texture
    void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif

