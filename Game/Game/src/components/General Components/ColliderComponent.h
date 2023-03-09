#pragma once
#include "../General Components/Transform.h"
#include "../../utils/Collisions.h"
#include "../Card Components/HitboxComponent.h"
#include <vector>
class GameObject;
class ColliderComponent : public Component
{
private:
	vector <HitboxComponent*> functions;
	grpId target;
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	ColliderComponent(grpId list);
	virtual void update();
	void hasCollided();
	void addFunction(HitboxComponent* funct);
};