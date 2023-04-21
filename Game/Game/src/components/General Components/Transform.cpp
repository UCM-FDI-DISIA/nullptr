#include "Transform.h"
#include <iostream>
#include "../../core/SDLApplication.h"

//Constructora por defecto
Transform::Transform() : initialPosition_(Vector2D()), position_(Vector2D()), velocity_(Vector2D()), anchorPoint_(Vector2D()), width_(0), height_(0), rotation_(0) {
}

//Constructora por copia
Transform::Transform(Transform* other) {
	initialPosition_ = other->initialPosition_;
	position_ = other->initialPosition_;
	velocity_ = other->velocity_;
	anchorPoint_ = other->anchorPoint_;
	width_ = other->width_;
	height_ = other->height_;
	rotation_ = other->rotation_;
}

//Constructora normal
Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r) : initialPosition_(pos), position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r) {
	anchorPoint_ = Vector2D(w / 2, h / 2);
}

//Constructora normal + anchorPoint
Transform::Transform(Vector2D pos, Vector2D vel, Vector2D anch, float w, float h, float r) : initialPosition_(pos), position_(pos), velocity_(vel), anchorPoint_(anch), width_(w), height_(h), rotation_(r) {
}


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
	position_ = position_ + (velocity_ * SDLApplication::instance()->getDeltaTimeSeconds());
}

//Actualiza constantemente la posicion con respecto la velocidad
void Transform::update() {
	double deltaTime = SDLApplication::instance()->getDeltaTimeSeconds();
	position_ = position_ + (velocity_ * deltaTime);
}