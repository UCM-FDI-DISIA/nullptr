#pragma once
#include "Component.h"
#include "../core/Vector2D.h"
#include "../data/constants.h"

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
	float width_;
	float height_;
	float rotation_;
	SDL_Point* anchorPoint_;
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

	//devuelve el centro del objeto
	inline Vector2D getCenter() {
		return position_ + Vector2D(width_ / 2, height_ / 2);
	};


	// Setea posición		
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

	
	inline void setAnchorPoint(int x, int y) {
		if (anchorPoint_ == nullptr) anchorPoint_ = new SDL_Point();
		anchorPoint_->x = x;
		anchorPoint_->y = y;
	}

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

	//Devuelve un rectangulo rotado de SDL
	inline SDL_Rect getRotatedRect() {

		double radians = rotation_ * (M_PI / 180.0);

		// Calcula las coordenadas de los cuatro vértices del rectángulo en relación con el punto de anclaje
		double cos_angle = cos(radians);
		double sin_angle = sin(radians);
		int x1 = -anchorPoint_->x * cos_angle - anchorPoint_->y * sin_angle;
		int y1 = anchorPoint_->x * sin_angle - anchorPoint_->y * cos_angle;
		int x2 = (width_ - anchorPoint_->x) * cos_angle - anchorPoint_->y * sin_angle;
		int y2 = (width_ - anchorPoint_->x) * sin_angle + anchorPoint_->y * cos_angle;
		int x3 = (width_ - anchorPoint_->x) * cos_angle - (height_ - anchorPoint_->y) * sin_angle;
		int y3 = (height_ - anchorPoint_->y) * sin_angle + (width_ - anchorPoint_->x) * cos_angle;
		int x4 = -anchorPoint_->x * cos_angle - (height_ - anchorPoint_->y) * sin_angle;
		int y4 = (height_ - anchorPoint_->y) * cos_angle - anchorPoint_->x * sin_angle;

		// Calcula los valores x, y, w y h para el rectángulo rotado
		int min_x = min({ x1, x2, x3, x4 });
		int min_y = min({ y1, y2, y3, y4 });
		int max_x = max({ x1, x2, x3, x4 });
		int max_y = max({ y1, y2, y3, y4 });

		SDL_Rect rect;
		rect.x = position_.getX() + min_x;
		rect.y = position_.getY() + min_y;
		rect.w = max_x - min_x;
		rect.h = max_y - min_y;

		return rect;
	}

	//Devuelve el punto de anclaje
	inline SDL_Point* getAnchorPoint() {
		return anchorPoint_;
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
