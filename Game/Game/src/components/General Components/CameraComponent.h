#pragma once
#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
#include "../../gameObjects/GameObject.h"
#include "../Component.h"
#include "../General Components/Transform.h"

class CameraComponent : public Component {
private:
	Transform* transform;
	Transform* followObjectTransform;
	Vector2D followObjectInitialPosition;
public:
	// Identificador
	static const int id = _CAMERACOMPONENT;
	// Constructora
	CameraComponent();
	// Inicializa el componente
	virtual void initComponent();
	// Setea el objeto a seguir
	void setFollowObject(GameObject* followObject_);
	// Sigue la posicion del followObject
	void update();
};
#endif // !CAMERA_COMPONENT_H_
