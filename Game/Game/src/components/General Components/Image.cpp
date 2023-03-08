#include "Image.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/GameState.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr), cameraTransform(nullptr), flip(SDL_FLIP_NONE), scrollFactor(1) {}

// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		cameraTransform = gStt->getCamera()->getComponent<Transform>();
	}
}

// Dibuja en pantalla la textura en el rectángulo del transform
void Image::render() const {
	texture->render(getRect(), transform->getRotation(), transform->getAnchorPoint());
}

//Devuelve el rect dependiendo de la cámara
SDL_Rect Image::getRect() const{
	SDL_Rect rect = transform->getRect();

	if (cameraTransform != nullptr) {
		//Dependiendo de la posición de la cámara
		rect.x += cameraTransform->getRect().x * scrollFactor;
		rect.y += cameraTransform->getRect().y * scrollFactor;
	}
	
	return rect;
}

//Devuelve el rect dependiendo de la cámara
SDL_Rect Image::getFactoredRect(float srcRectRelativeWidth, float srcRectRelativeHeight) const {
	SDL_Rect rect = transform->getFactoredRect(srcRectRelativeWidth, srcRectRelativeHeight);

	//if (cameraTransform != nullptr) {
	//	//Dependiendo de la posición de la cámara
	//	rect.x += cameraTransform->getRect().x * scrollFactor;
	//	rect.y += cameraTransform->getRect().y * scrollFactor;
	//}

	return rect;
}


// Hace que el GameObject se renderice en función a la ventana, no a la cámara
void Image::attachToCamera() {
	cameraTransform = nullptr;
}

// Flipea la imagen horizontalmente
void Image::flipHorizontal() {
	flip = SDL_FLIP_HORIZONTAL;
}

// Flipea la imagen verticalmente
void Image::flipVertical() {
	flip = SDL_FLIP_VERTICAL;
}

void Image::flipNone() {
	flip = SDL_FLIP_NONE;
}

void Image::setScrollFactor(float _factor) {
	if (cameraTransform != nullptr) {
		scrollFactor = _factor;
	}
}