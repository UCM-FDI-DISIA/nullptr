#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../gameObjects/GameObject.h"
#include "../../utils/Collisions.h"
class ColliderComponent: public Component
{
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	bool hasCollided(Transform* other) {
		Vector2D& pos1 = gObj->getComponent<Transform>()->getPos();
		float width1 = gObj->getComponent<Transform>()->getWidth();
		float height1 = gObj->getComponent<Transform>()->getHeight();
		float rot1 = gObj->getComponent<Transform>()->getRotation();
		Vector2D anch1 = gObj->getComponent<Transform>()->getAnchorPoint();
		Vector2D& pos2 = other->getPos();
		float width2 = other->getWidth();
		float height2 = other->getHeight();
		float rot2 = other->getRotation();
		Vector2D anch2 = other->getAnchorPoint();

		return Collisions::collidesWithRotation(pos1, width1, height1, rot1, anch1,
												pos2, width2, height2, rot2, anch2);
	}
};
