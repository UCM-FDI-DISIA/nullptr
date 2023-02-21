#pragma once
#include "Component.h"
#include "Transform.h"
#include "../core/GameObject.h"
class ColliderComponent: public Component
{
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	bool hasCollided(Transform* other) {
		SDL_Rect aux = gObj->getComponent<Transform>()->getRect();
		SDL_Rect aux1 = other->getRect();
		return SDL_HasIntersection(&aux, &aux1);
	}
};
