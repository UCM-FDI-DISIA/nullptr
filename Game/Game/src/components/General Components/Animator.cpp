#include "Animator.h"
#include "../../core/SDLApplication.h"


void Animator::createAnim(string key, Animation anim) {
	anims.insert({ key, anim });
	currentFrame = anim.startFrame;
}

// Crea una animacion nueva
void Animator::createAnim(string key, int start, int end, int rate, int _rep) {
	createAnim(key, Animation(start, end, rate, _rep));
}

// Empieza una nueva animacion
void Animator::play(string key) {
	currentAnimKey = key;
	currentAnimation = &anims[currentAnimKey];
	currentFrame = currentAnimation->startFrame;
	repetitions = 0;
	currTime = 0;
}

// Para la animacion actual
void Animator::stop() {
	currentAnimation = nullptr;
}

// Continua la ultima animacion
void Animator::resume() {
	currentAnimation = &anims[currentAnimKey];
}

// Actualiza el frame actual dependiendo del frameRate
void Animator::update() {

	if (currentAnimation != nullptr) {
		if (currTime >= (1000 / currentAnimation->frameRate)) {

			if (currentAnimation->repeat != repetitions) {
				// Devuelve el siguiente frame a renderizar
				currentFrame = currentAnimation->startFrame + ((currentFrame + 1 - currentAnimation->startFrame) % (currentAnimation->endFrame - currentAnimation->startFrame + 1));

				// Si ha terminado una iteracion de la animacion, se le resta una repeticion
				if (currentFrame == currentAnimation->endFrame) {

					++repetitions;
				}
			}

			else currentFrame = currentAnimation->startFrame;

			
			currTime = 0;
		}
		currTime += SDLApplication::instance()->getDeltaTime();
	}
}



// Renderiza el frame actual
void Animator::render() const {
	SDL_Rect srcRect;
	srcRect.x = (currentFrame % cols) * fw;
	srcRect.y = ((currentFrame / cols) % rows) * fh;
	srcRect.w = fw;
	srcRect.h = fh;
	
	texture->render(srcRect, getRect(), 0, nullptr, flip);

	
}