#include "Pointer.h"
#include "../../core/SDLApplication.h"

// Inicializa el objeto
void Pointer::initGameObject() {
	transform = addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, POINTER_WIDTH, POINTER_HEIGHT, 0);
	imageComponent = addComponent<Image>(SDLApplication::instance()->getTexture(POINTER));
	imageComponent->attachToCamera();
	pointerComponent = addComponent<PointerComponent>(gStt);
}

// Establece si se quiere renderizar el puntero o no
void Pointer::setShowPointer(bool value) {
	if (getShowPointer() != value) {
		if (value) {
			imageComponent = addComponent<Image>(SDLApplication::instance()->getTexture(POINTER));
			imageComponent->attachToCamera();
		}
		else {
			imageComponent = nullptr;
			removeComponent<Image>();
		}
	}
}