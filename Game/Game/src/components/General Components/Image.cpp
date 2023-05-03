#include "Image.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/GameState.h"

// Constructor
Image::Image(Texture* _texture) : texture(_texture), transform(nullptr), cameraTransform(nullptr), flip(SDL_FLIP_NONE), scrollFactor(1) {}

// Inicializa el componente y asigna su puntero a transform
void Image::initComponent() {
	transform = gObj->getComponent<Transform>();
	assert(transform != nullptr);
	dettachFromCamera();
}

// Dibuja en pantalla la textura en el rect�ngulo del transform
void Image::render() const {
	texture->changeAlpha(alpha);
	texture->changeTint(r,g,b);
	texture->render(getRect(), transform->getRotation(), transform->getAnchorPointSDL(), flip);
	texture->changeAlpha(255);
	texture->changeTint(255, 255, 255);
}

//Devuelve el rect dependiendo de la c�mara
SDL_Rect Image::getRect() const{
	SDL_Rect rect = transform->getRect();

	if (cameraTransform != nullptr) {
		//Dependiendo de la posici�n de la c�mara
		rect.x += cameraTransform->getRect().x * scrollFactor;
		rect.y += cameraTransform->getRect().y * scrollFactor;
	}
	
	return rect;
}

//Devuelve el rect dependiendo de la c�mara
SDL_Rect Image::getFactoredRect(float srcRectRelativeWidth, float srcRectRelativeHeight) const {
	SDL_Rect rect = transform->getFactoredRect(srcRectRelativeWidth, srcRectRelativeHeight);

	//if (cameraTransform != nullptr) {
	//	//Dependiendo de la posici�n de la c�mara
	//	rect.x += cameraTransform->getRect().x * scrollFactor;
	//	rect.y += cameraTransform->getRect().y * scrollFactor;
	//}

	return rect;
}


// Hace que el GameObject se renderice en funci�n a la ventana, no a la c�mara
void Image::attachToCamera() {
	cameraTransform = nullptr;
}

// Hace que el GameObject se renderice en función a la cámara, no a la ventana
void Image::dettachFromCamera() {
	if (gStt != nullptr) {
		cameraTransform = gStt->getCamera()->getComponent<Transform>();
	}
}

// Flipea la imagen horizontalmente
void Image::flipHorizontal() {
	flip = SDL_FLIP_HORIZONTAL;
}

// Flipea la imagen verticalmente
void Image::flipVertical() {
	flip = SDL_FLIP_VERTICAL;
}

// Desflipea la imagen
void Image::flipNone() {
	flip = SDL_FLIP_NONE;
}

// Establece el factor de deslice para el efecto parallax
void Image::setScrollFactor(float _factor) {
	if (cameraTransform != nullptr) {
		scrollFactor = _factor;
	}
}