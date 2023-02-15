#include "Animator.h"

// Crea una animación nueva
void Animator::createAnim(string key, int start, int end, int rate, int _rep) {
	Animation newAnim = Animation(start, end, rate, _rep);
	anims.insert({ key, newAnim });
	currentFrame = start;
}

// Starts a new animation
void Animator::play(string key) {
	currentAnimKey = key;
	currentAnimation = &anims[currentAnimKey];
	currentFrame = currentAnimation->startFrame;
	repetitions = 0;
	startTime = SDL_GetTicks();
}

// Stops the current animation
void Animator::stop() {
	currentAnimation = nullptr;
}

// Resumes the last animation played
void Animator::resume() {
	currentAnimation = &anims[currentAnimKey];
}

//
void Animator::update() {
	if (currentAnimation != nullptr) {
		if (SDL_GetTicks() - startTime >= (1000 / currentAnimation->frameRate)) {

			if (currentAnimation->repeat != repetitions) {
				// Devuelve el siguiente frame a renderizar
				currentFrame = currentAnimation->startFrame + ((currentFrame + 1) % (currentAnimation->endFrame - currentAnimation->startFrame + 1));

				// Si ha terminado una iteracion de la animacion, se le resta una repeticion
				if (currentFrame == currentAnimation->endFrame) {

					++repetitions;
				}
			}

			else currentFrame = currentAnimation->startFrame;

			startTime = SDL_GetTicks();
		}
	}
	else currentFrame = 0;
}

//
void Animator::render() const {
	SDL_Rect srcRect;
	srcRect.x = (currentFrame % cols) * fw;
	srcRect.y = ((currentFrame / cols) % rows) * fh;
	srcRect.w = fw;
	srcRect.h = fh;
	
	texture->render(srcRect, getRect());
}