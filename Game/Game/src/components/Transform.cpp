#include "Transform.h"

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
	Vector2D aux = position_ - point; // Sacas la dirección entre el objeto y el objetivo
	rotation_ = aux.angle(velocity_); // Sacas el ángulo entre la dirección que tienes y la que necesitas
	velocity_ = velocity_.rotate(rotation_); // Rotas la dirección que tienes hasta la que necesitas.
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
	rotation_ = rotation;
	velocity_ = velocity_.rotate(rotation_);
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