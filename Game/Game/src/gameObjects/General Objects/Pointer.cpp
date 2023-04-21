#include "Pointer.h"
#include "../../core/SDLApplication.h"

// Constructora
void Pointer::initGameObject() {
	transform = addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("POINTER_WIDTH"), Constant::getInt("POINTER_HEIGHT"), 0);
	imageComponent = addComponent<Image>(SDLApplication::instance()->getTexture(Constant::getString("POINTER")));
	imageComponent->attachToCamera();
	pointerComponent = addComponent<PointerComponent>(gStt);
}