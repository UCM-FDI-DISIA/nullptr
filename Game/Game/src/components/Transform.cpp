#include "Transform.h"
#include <iostream>

//Constructora por defecto
Transform::Transform() : initialPosition_(VECTOR_ZERO), position_(VECTOR_ZERO), velocity_(VECTOR_ZERO), width_(0), height_(0), rotation_(0), anchorPoint_(nullptr) {}

//Constructora normal
Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r) : initialPosition_(pos), position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r), anchorPoint_(nullptr) {}

Transform::~Transform() {}

//Rota el vector de velocidad para que se dirija hacia el punto definido
void Transform::lookAt(Vector2D point) {
	Vector2D aux = point- position_; // Saca el vector desde el punto a la posición
	float rotation = velocity_.angle(aux); // Saca los angulos entre el vector velocidad y el necesario
	velocity_ = velocity_.rotate(rotation); // Rota el vector velocidad
}

// Devuelve la distancia en valor absoluto desde un punto a otro
float Transform::getDistance(Vector2D other) {
	float x = other.getX() - position_.getX();
	float y = other.getY() - position_.getY();
	return abs(sqrt(x * x + y * y));
}

//Rota el vector de velocidad
void Transform::rotate(float rotation) {
	rotation_ += rotation;
	velocity_ = velocity_.rotate(rotation);
}

//Quita la rotacion al vector de velocidad
void Transform::unrotate() {
	velocity_ = velocity_.rotate(-rotation_);
	rotation_ = 0;
}

//Actualiza la posicion con el vector de velocidad
void Transform::move() {
	position_ = position_ + velocity_;
}

//Actualiza constantemente la posicion con respecto la velocidad
void Transform::update() {
	position_ = position_ + velocity_;
}