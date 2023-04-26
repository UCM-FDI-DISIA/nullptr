#include "Tuto.h"
#include "../../core/SDLApplication.h"

// Inicializa el objeto
void Tuto::initGameObject(Transform* pl) {
	addComponent<Transform>(Vector2D(WIN_WIDTH - 128 * 2, WIN_HEIGHT - 128 * 2),
		VECTOR_ZERO, COMPANION_WIDTH, COMPANION_HEIGHT);

	myAnim = addComponent<Animator>(SDLApplication::getTexture(COMPANION_TEXTURE),
		COMPANION_SPRITE_WIDTH, COMPANION_SPRITE_HEIGHT, 6, 5);
	myAnim->createAnim(IDLE, 0, 1, 5, -1);
	myAnim->play(IDLE);

	l = addComponent<LerpComponent>(pl);
}