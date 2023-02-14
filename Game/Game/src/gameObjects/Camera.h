#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "../core/GameObject.h"
#include "../core/Vector2D.h"

class Camera : public GameObject {
private:
	Vector2D* pos;
public:
	// Constructor por defecto
	Camera();
	// Setea la posicion central de la camara
	void setPosition(Vector2D pos);
	// Devuelve puntero a la posicion central de la camara
	Vector2D* getPosition();
};
#endif // !CAMERA_H_
