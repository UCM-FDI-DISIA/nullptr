#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "../core/GameObject.h"
#include "../data/constants.h"
#include "../components/Transform.h"
#include "../components/CameraComponent.h"

class Camera : public GameObject {
private:
	float posX, posY, width, height, rotation;
	Transform* transform;
	CameraComponent* cameraComponent;
	GameObject* followObject;
	Transform* followObjectTransform;

public:
	// Constructoras
	// Por defecto
	Camera();
	// Con objeto a seguir
	Camera(GameObject* _followObject);
	Camera(GameObject* _followObject, SDL_Rect rect, float _rotation = 0);
	Camera(GameObject* _followObject, float posX, float posY, float width, float height, float rotation = 0);

};
#endif // !CAMERA_H_
