#pragma once
#include "Component.h"
#include "../core/Vector2D.h"
#include "../data/constants.h"

/*  
	Clase que implementa el transform de los objetos del juego
	con 3 vectores: posicion initial, posicion actual y velocidad, y ademas
	una altura, anchura y un factor de rotacion.
	una altura, anchura y un factor de rotacion.
	Dispone de funciones para rotar y desrotar el vector de 
	velocidad y la posicion se actualiza en el update respecto
	a la velocidad. 
	Dispone de getters y setters para los parametros menos la rotacion.
*/

class Transform : public Component {
private:
	Vector2D initialPosition_;
	Vector2D position_;
	Vector2D velocity_;
	float width_;
	float height_;
	float rotation_;
public:

	static const int id = _TRANSFORM;
	Transform();
	Transform(Vector2D pos, Vector2D vel, float w = 0, float h = 0, float r = 0);
	virtual ~Transform();

	// Devuelve la posición
	inline Vector2D& getPos() {
		return position_;
	};

	// Devuelve la velocidad
	inline Vector2D& getVel() {
		return velocity_;
	};

	// Setea posición		
	inline void setPos(Vector2D newPos) {
		position_ = newPos;
	};

	// Setea velocidad
	inline void setVel(Vector2D newVel) {
		velocity_ = newVel;
	};

	// Setea height
	inline void setHeight(float newHeight) {
		height_ = newHeight;
	}

	// Setea width
	inline void setWidth(float newWidth) {
		width_ = newWidth;
	}

	// Devuelve height
	inline float getHeight() {
		return height_;
    }

	// Devuelve width
	inline float getWidth() {
		return width_;
	}

	inline Vector2D getInitialPosition() { return initialPosition_; }

	inline SDL_Rect getRect() {
		SDL_Rect rect;
		rect.x = position_.getX();
		rect.y = position_.getY();
		rect.w = width_;
		rect.h = height_;

		return rect;
	}
	void lookAt(Vector2D point);
	void rotate(float rotation);
	void unrotate();
	void move();
	virtual void update();
};
