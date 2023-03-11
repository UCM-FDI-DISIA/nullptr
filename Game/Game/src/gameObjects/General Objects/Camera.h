#pragma once
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
	// Constructora
	Camera();

	// Destructora
	~Camera();

	// Asigna el objeto a seguir
	void startFollowObject(GameObject* followObject_);

	// Devuelve el followObject
	GameObject* getFollowObject();

	// Devuelve la posicion de la camara
	Vector2D getOffset() const;
};
