#include "Pointer.h"
#include "../../core/SDLApplication.h"

// Constructora
Pointer::Pointer() {
	transform = addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, POINTER_WIDTH, POINTER_HEIGHT, 0);
	addComponent<Image>(SDLApplication::instance()->getTexture(POINTER));
	pointerComponent = addComponent<PointerComponent>();
}