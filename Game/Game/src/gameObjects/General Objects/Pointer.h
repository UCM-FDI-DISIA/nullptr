#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General components/PointerComponent.h"
#include "../../components/General components/Image.h"

class Pointer : public GameObject {
private:
	Transform* followObjectTransform;
	Transform* transform;
	PointerComponent* pointerComponent;
	Image* imageComponent;
public:
	// Inicializa el objeto
	void initGameObject();
};