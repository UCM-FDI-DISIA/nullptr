#include "Transform.h"

Transform::Transform() {
	position_ = Vector2D(0, 0);
	velocity_ = Vector2D(0, 0);
	width_ = 0;
	height_ = 0;
	rotation_ = 0;
}

Transform::Transform(Vector2D pos, Vector2D vel, float w, float h, float r) {
	position_ = pos;
	velocity_ = vel;
	width_ = w;
	height_ = h;
	rotation_ = r;
}

Transform::~Transform(){}

// Rota el vector de velocidad para que se dirija hacia el punto definido
void Transform::lookAt(Vector2D point) {
	Vector2D aux = position_ - point; // Sacas la direcci�n entre el objeto y el objetivo
	rotation_ = aux.angle(velocity_); // Sacas el �ngulo entre la direcci�n que tienes y la que necesitas
	velocity_ = velocity_.rotate(rotation_); // Rotas la direcci�n que tienes hasta la que necesitas.
}
// Devuelve un float con el modulo de la distancia entre este y otro punto
float Transform::getDistance(Vector2D other)
{
	float x = other.getX() - position_.getX();
	float y = other.getY() - position_.getY();
	return abs(sqrt(x * x + y * y));
}

// Rota el vector de velocidad
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

