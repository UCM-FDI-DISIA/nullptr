#include "Animator.h"
#include "../../core/SDLApplication.h"

void Animator::createAnim(string key, Animation anim) {
	//anims.insert({ key, anim });
	anims[key] = anim;
	currentFrame = anim.startFrame;
}

// Crea una animacion nueva
void Animator::createAnim(string key, int start, int end, int rate, int _rep) {
	createAnim(key, Animation(start, end, rate, _rep));
}

// Empieza una nueva animacion
void Animator::play(string key) {
	Animation* prevAnim = currentAnimation;
	string prevKey = currentAnimKey;

	currentAnimKey = key;
	currentAnimation = &anims[currentAnimKey];

	// Si son dos animaciones enlazadas entre sí, recoloca el frame actual para ajustarse a la nueva animación
	if ((prevAnim != nullptr && prevAnim->linked && currentAnimation->linked && linkedAnimations.at(prevKey).count(currentAnimKey))) {
		currentFrame -= prevAnim->startFrame;
		currentFrame += currentAnimation->startFrame;
	}
	// Si no son animaciones enlazadas se inicia la animción de 0
	else {
		currentFrame = (currentAnimation->backwards ? currentAnimation->endFrame : currentAnimation->startFrame);
		repetitions = 0;
		currTime = 0;
	}
}

// Para la animacion actual
void Animator::stop() {
	currentAnimation = nullptr;
}

// Continua la ultima animacion
void Animator::resume() {
	currentAnimation = &anims[currentAnimKey];
}

// Inicia una nueva animaci�n si es diferente a la actual
bool Animator::playDiff(string key) {
	if (!isCurrentAnimation(key) || !isPlaying()) {
		play(key);
		return true;
	}
	return false;
}

// Actualiza el frame actual dependiendo del frameRate
void Animator::update() {
	if (currentAnimation != nullptr) {
		if (currTime >= (1000 / currentAnimation->frameRate)) {
			if (currentAnimation->repeat != repetitions) {
				if (!currentAnimation->backwards) {
					// Devuelve el siguiente frame a renderizar
					currentFrame = currentAnimation->startFrame + ((currentFrame + 1 - currentAnimation->startFrame) % (currentAnimation->endFrame - currentAnimation->startFrame + 1));
				}
				else {
					currentFrame = currentAnimation->endFrame - ((-currentFrame + 1 + currentAnimation->endFrame) % (currentAnimation->endFrame - currentAnimation->startFrame + 1));
				}
				// Si ha terminado una iteracion de la animacion, se le resta una repeticion
				if ((currentFrame == currentAnimation->endFrame && !currentAnimation->backwards) || (currentFrame == currentAnimation->startFrame && currentAnimation->backwards)) {

					++repetitions;
				}
			}

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
	srcRect.w = fw * srcRectRelativeWidth;
	srcRect.h = fh * srcRectRelativeHeight;
	texture->changeTint(r, g, b);
	texture->changeAlpha(alpha);
	// Si debo renderizar menos del ancho de la textura original
	if (srcRectRelativeWidth < 1 || srcRectRelativeHeight < 1) {
		texture->render(srcRect, getFactoredRect(srcRectRelativeWidth, srcRectRelativeHeight),
			transform->getRotation(), nullptr, flip);
	}
	else texture->render(srcRect, getRect(), transform->getRotation(), nullptr, flip);
	texture->changeAlpha(255);
	texture->changeTint(255, 255, 255);
}


// Asigna el valor para el cambio del tamaño del srcRect
void Animator::setSrcRectRelativeWidth(float rw) {
	if (rw > 1) rw = 1;
	else if (rw < 0) rw = 0;
	srcRectRelativeWidth = rw;
}

// Asigna el valor para el cambio del tamaño del srcRect
void Animator::setSrcRectRelativeHeight(float rh) {
	if (rh > 1) rh = 1;
	else if (rh < 0) rh = 0;
	srcRectRelativeHeight = rh;
}

void Animator::linkAnimations(std::string key1, std::string key2) {
	auto it1 = anims.find(key1);
	if (it1 == anims.end()) throw std::out_of_range("Couldn't link animations. Animation '" + key1 + "' was never declared.");
	auto it2 = anims.find(key2);
	if (it2 == anims.end()) throw std::out_of_range("Couldn't link animations. Animation '" + key2 + "' was never declared.");

	it1->second.linked = true;
	it2->second.linked = true;

	linkedAnimations[key1].insert(key2);
	linkedAnimations[key2].insert(key1);
}