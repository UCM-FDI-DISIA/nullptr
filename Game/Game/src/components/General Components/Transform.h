#pragma once
#include "../Component.h"
#include "../../core/Vector2D.h"
#include "../../data/constants.h"

/*  
	Clase que implementa el transform de los objetos del juego
	con 3 vectores: posicion initial, posicion actual y velocidad, y ademas
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
	Vector2D anchorPoint_;
	float width_;
	float height_;
	float rotation_;
public:

	static const int id = _TRANSFORM;
	Transform();
	Transform(Vector2D pos, Vector2D vel, float w = 0, float h = 0, float r = 0);
	Transform(Vector2D pos, Vector2D vel, Vector2D anch, float w = 0, float h = 0, float r = 0);
	virtual ~Transform();

	// Devuelve la posici�n
	inline Vector2D& getPos() {
		return position_;
	};

	inline float getX() {
		return position_.getX();
	}

	inline float getY() {
		return position_.getY();
	}

	// Devuelve la velocidad
	inline Vector2D& getVel() {
		return velocity_;
	};

	inline Vector2D& getAnchorPoint() {
		return anchorPoint_;
	}

	//devuelve el centro del objeto
	inline Vector2D getCenter() {
		return position_ + Vector2D(width_ / 2, height_ / 2);
	};


	// Setea posici�n		
	inline void setPos(Vector2D newPos) {
		position_ = newPos;
	};

	// Setea el valor de Y del transform
	inline void setY(int y) {
		position_ = Vector2D(position_.getX(), y);
	}

	//Setea el valor de X en el transform
	inline void setX(int x) {
		position_ = Vector2D(x, position_.getY());
	}

	// Setea velocidad
	inline void setVel(Vector2D newVel) {
		velocity_ = newVel;
	};

	
	inline void setAnchorPoint(Vector2D newAnch) {
		anchorPoint_= newAnch;
	}

	// Setea height
	inline void setHeight(float newHeight) {
		height_ = newHeight;
	}

	// Setea width
	inline void setWidth(float newWidth) {
		width_ = newWidth;
	}

	// Setea la rotacion
	inline void setRotation(int _rotation) {
		rotation_ = _rotation;
	}

	// Devuelve height
	inline float getHeight() {
		return height_;
    }

	// Devuelve width
	inline float getWidth() {
		return width_;
	}

	//Devuelve la posicion inicial
	inline Vector2D getInitialPosition() { return initialPosition_; }

	//Devuele un rectangulo SDL
	inline SDL_Rect getRect() {
		SDL_Rect rect;
		rect.x = position_.getX();
		rect.y = position_.getY();
		rect.w = width_;
		rect.h = height_;

		return rect;
	}

	// Devuelve un rectangulo SDL con un factor que cambia el width devuelto
	inline SDL_Rect getFactoredRect(float srcRectRelativeWidth, float srcRectRelativeHeight) {
		SDL_Rect rect;
		rect.x = position_.getX();
		rect.y = position_.getY();
		rect.w = width_ * srcRectRelativeWidth;
		rect.h = height_ * srcRectRelativeHeight;

		return rect;
	}

	//Devuelve el punto de anclaje
	inline SDL_Point* getAnchorPointSDL() {
		SDL_Point* point = new SDL_Point;
		point->x = anchorPoint_.getX();
		point->y = anchorPoint_.getY();
		return point;
	};


	//Devuelve la rotacion
	inline float getRotation() {
		return rotation_;
	};


	// Devuelve la distancia en valor absoluto desde un punto a otro
	float getDistance(Vector2D other);
	void lookAt(Vector2D point);
	void rotate(float rotation);
	void unrotate();
	void move();
	virtual void update();
};
