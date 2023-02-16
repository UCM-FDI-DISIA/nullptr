#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"

/*
	Se encarga de renderizar correctamente la imagen del objeto teniendo en cuenta
	si tiene una camara atachada
*/

class Image : public Component {
protected:
	Texture* texture;
	Transform* transform;
	Transform* cameraTransform;
public:
	static const int id = _IMAGE;
	// Constructora
	Image(Texture* _texture, Transform* _cameraTransform = nullptr);
	// Inicializa el componente y asigna su puntero a transform
	virtual void initComponent();
	// Dibuja en pantalla la textura en el rectángulo del transform
	virtual void render() const;
	virtual SDL_Rect getRect() const;
};
#endif // !IMAGE_H_
