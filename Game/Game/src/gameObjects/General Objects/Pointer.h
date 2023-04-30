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
	// Devuelve si renderiza el puntero o no
	inline bool getShowPointer() { return imageComponent != nullptr; }
	// Establece si se quiere renderizar el puntero o no
	void setShowPointer(bool value);
};