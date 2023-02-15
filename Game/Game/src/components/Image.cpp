#include "Image.h"
#include "../core/GameObject.h"

// Constructor
Image::Image(Texture* _texture, Transform* _cameraTransform) : texture(_texture), transform(nullptr), cameraTransform(_cameraTransform) {}


// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
}

// Dibuja en pantalla la textura en el rectángulo del transform
void Image::render() const {
	
	texture->render(getRect());
}

// Devuelve el rect dependiendo de la camara
SDL_Rect Image::getRect() const {
	SDL_Rect rect = transform->getRect();

	if (cameraTransform != nullptr) {
		// Dependiendo de la posicion de la camara
		rect.x += cameraTransform->getRect().x;
		rect.y += cameraTransform->getRect().y;
	}

	return rect;
}