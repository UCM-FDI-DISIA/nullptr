#include "Texture.h"
#include <iostream>

using namespace std;

// Constructor
Texture::Texture(SDL_Renderer* r, string filename, uint numRows, uint numCols) : renderer(r) { load(filename, numRows, numCols); }

// Destroys the texture 
void Texture::_free() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

// Loads a texture from the specified
void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw SDLError(IMG_GetError());
	
	_free();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw SDLError("Error loading texture from " + filename);
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

// Draws single texture on screen
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

// Draws texture depending of the frame we want from texture
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}
