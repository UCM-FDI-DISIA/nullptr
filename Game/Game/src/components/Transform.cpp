#include "Transform.h"

Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r) {
	position_ = pos;
	velocity_ = vel;
	width_ = w;
	height_ = h;
	rotation_ = r;
}

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
}

SDL_Rect Transform::getRect() {
	SDL_Rect rect;
	rect.x = position_.getX
	rect.y = this->pos.getY();
	rect.w = this->width * this->size;
	rect.h = this->height * this->size;

	return rect;
}