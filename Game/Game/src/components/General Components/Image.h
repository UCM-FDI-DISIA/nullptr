#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_
#include "../Component.h"
#include "Transform.h"
#include "../../sdlutils/Texture.h"

/*
	Se encarga de renderizar correctamente la imagen del objeto teniendo en cuenta
	si tiene una camara atachada
*/

class Image : public Component {
protected:
	Texture* texture;
	Transform* transform;
	//Transform* cameraTransform;
	SDL_RendererFlip flip;
	float scrollFactor;
public:
	Transform* cameraTransform;
	static const int id = _IMAGE;
	// Constructora
	Image(Texture* _texture);
	// Inicializa el componente y asigna su puntero a transform
	virtual void initComponent();
	// Dibuja en pantalla la textura en el rectángulo del transform
	virtual void render() const;
	virtual SDL_Rect getRect() const;
	virtual SDL_Rect getFactoredRect(float srcRectRelativeWidth, float srcRectRelativeHeight) const;
	// Hace que el GameObject se renderice en función a la ventana, no a la cámara
	void attachToCamera();
	// Hace que el GameObject se renderice en función a la cámara, no a la ventana
	void dettachFromCamera();
	// Flipea la imagen horizontalmente
	void flipHorizontal();
	// Flipea la imagen verticalmente
	void flipVertical();
	// Desflipea la imagen
	void flipNone();
	// 
	void setScrollFactor(float _factor);
};
#endif // !IMAGE_H_
