#include "Image.h"
#include "../core/GameObject.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr) {}


// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
}

// Dibuja en pantalla la textura en el rectángulo del transform
void Image::render() const {
	texture->render(transform->getRect());
}