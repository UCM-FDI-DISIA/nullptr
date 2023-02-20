#include "Image.h"
#include "../core/GameObject.h"
#include "../scenes/GameState.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr), cameraTransform(nullptr) {}


// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		cameraTransform = gStt->getCamera()->getComponent<Transform>();
	}
}

// Dibuja en pantalla la textura en el rectángulo del transform
void Image::render() const {
	texture->render(getRect(), transform->getRotation(),transform->getAnchorPoint());
}

//Devuelve el rect dependiendo de la cámara
SDL_Rect Image::getRect() const{
	SDL_Rect rect = transform->getRect();

	if (cameraTransform != nullptr) {
		//Dependiendo de la posición de la cámara
		rect.x += cameraTransform->getRect().x;
		rect.y += cameraTransform->getRect().y;
	}
	
	return rect;
}


// Hace que el GameObject se renderice en función a la ventana, no a la cámara
void Image::attachToCamera() {
	cameraTransform = nullptr;
}