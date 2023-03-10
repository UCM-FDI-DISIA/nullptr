#include "Pointer.h"
#include "../../core/SDLApplication.h"

// Constructora
void Pointer::initGameObject() {
	transform = addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, POINTER_WIDTH, POINTER_HEIGHT, 0);
	imageComponent = addComponent<Image>(SDLApplication::instance()->getTexture(POINTER));
	imageComponent->attachToCamera();
	pointerComponent = addComponent<PointerComponent>(gStt);
}