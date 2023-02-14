#include "Camera.h"

/*
	Almacena una posicion inicializada en (0,0) que cambiará si existe un objeto Player
*/

// Constructora por defecto
Camera::Camera() : pos(new Vector2D(0,0)) {}

// Setea la posicion central de la camara
void Camera::setPosition(Vector2D pos_) {
	pos->setX(pos_.getX());
	pos->setY(pos_.getY());
}

// Devuelve punto a la posicion de la camara
Vector2D* Camera::getPosition() { return pos; }