#pragma once
#include "Component.h"
#include "Transform.h"
#include "../core/Manager.h"
class ColliderComponent: public Component
{
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	bool hasCollided(Transform* other) {
		return SDL_HasIntersection(&gObj->getComponent<Transform>()->getRect(), &other->getRect());
	}
};
