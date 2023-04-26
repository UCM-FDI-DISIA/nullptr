// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cmath>
#include <ostream>

/*
 * Clase que implementa vectores de 2 dimensiones y sus operaciones
 * correspondientes. Todas las operaciones generan un new Vector2D,
 * no modifican los vectores en los que operan. Los unicos metodos
 * que los modifican son los setters y el operando =
 */
class Vector2D {
public:

	// Constructores varios
	Vector2D() noexcept :
			x_(), y_() {
	}

	Vector2D(const Vector2D &v) :
			x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(Vector2D &&v) :
			x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(const Vector2D *v) :
			x_(v->getX()), y_(v->getY()) {
	}

	Vector2D(float x, float y) :
			x_(x), y_(y) {
	}

	~Vector2D() {
	}

	// getters
	inline float getX() const {
		return x_;
	}

	inline float getY() const {
		return y_;
	}

	// setters
	inline void setX(float x) {
		x_ = x;
	}

	inline void setY(float y) {
		y_ = y;
	}

	inline void set(float x, float y) {
		x_ = x;
		y_ = y;
	}

	inline void set(const Vector2D &v) {
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(const Vector2D &&v) {
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(const Vector2D *v) {
		x_ = v->x_;
		y_ = v->y_;
	}

	// Copia otro vector
	inline Vector2D& operator=(const Vector2D &v) {
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	// move assignment - not really needed
	inline Vector2D& operator=(const Vector2D &&v) {
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	// ** operaciones varias

	// longitud del vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2));
	}

	// normalizar vector
	inline Vector2D normalize() const {
		if (magnitude() == 0) return *this;
		return *this / magnitude();
	}

	//Rotacion en el sentido de las agujas del reloj
	Vector2D rotate(float degrees) const;

	//Saca el angulo entre dos vectores
	float angle(const Vector2D &v) const;

	// resta de vectores
	inline Vector2D operator-(const Vector2D &v) const {
		return Vector2D(x_ - v.x_, y_ - v.y_);
	}

	// suma de vectores
	inline Vector2D operator+(const Vector2D &v) const {
		return Vector2D(x_ + v.x_, y_ + v.y_);
	}

	// multiplicación por constante
	inline Vector2D operator*(float d) const {
		return Vector2D(x_ * d, y_ * d);
	}

	// division por constante
	inline Vector2D operator/(float d) const {
		return Vector2D(x_ / d, y_ / d);
	}

	// multiplicacion escalar
	inline float operator *(const Vector2D &d) const {
		return d.x_ * x_ + d.y_ * y_;
	}

private:
	float x_;  // primera coordenada
	float y_;  // segunda coordenada
};

// es necesario para poder imprimir el vector en pantalla
std::ostream& operator<<(std::ostream &os, const Vector2D &v);
