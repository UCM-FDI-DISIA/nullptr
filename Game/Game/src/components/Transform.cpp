#include "Transform.h"

Transform::Transform() : position_(Vector2D(0, 0)), velocity_(Vector2D(0, 0)), width_(0), height_(0), rotation_(0), center_(Vector2D(0,0)) {}

Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r, const Vector2D& center) : position_(pos), velocity_(vel), width_(w), height_(h), rotation_(r), center_(center) {}

Transform::~Transform(){}

//Rota el vector de velocidad para que se dirija hacia el punto definido
void Transform::lookAt(Vector2D point) {
	Vector2D aux = position_ - point;
	float rotation = aux.angle(velocity_);
	velocity_ = velocity_.rotate(rotation_);
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

void Transform::update() {
	position_ = position_ + velocity_;
	//position_ = position_ + center_ + velocity_;
}

