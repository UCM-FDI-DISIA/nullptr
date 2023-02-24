#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include "../GameObject.h"
#include "../../core/Vector2D.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/CameraComponent.h"

class Camera : public GameObject {
private:
	Transform* transform;
	CameraComponent* cameraComponent;
	GameObject* followObject;
public:
	// Constructor por defecto
	Camera();
	// Destructora
	~Camera();
	// Asigna el objeto a seguir
	void startFollowObject(GameObject* followObject_);
	// Devuelve el followObject
	GameObject* getFollowObject();

	Vector2D getOffset() const;
};
#endif // !CAMERA_H_
