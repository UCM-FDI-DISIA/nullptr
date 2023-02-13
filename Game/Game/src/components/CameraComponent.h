#pragma once
#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_
#include "../core/GameObject.h"
#include "../components/Component.h"
#include "../components/Transform.h"

class CameraComponent : public Component {
private:
	Transform* transform;

public:
	static const int id = _CAMERACOMPONENT;

	// Constructora
	CameraComponent();

	// Inicializa el componente
	virtual void initComponent();

	// Renderiza los limites
	//virtual void render() const;


};
#endif //!CAMERA_COMPONENT_H_