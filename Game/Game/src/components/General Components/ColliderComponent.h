#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../utils/Collisions.h"
#include <vector>
class GameObject;
class ColliderComponent : public Component
{
private:
	vector <CallBackCol> functions;
	grpId target;
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	ColliderComponent(grpId list);
	virtual void update();
	void hasCollided();
	void addFunction(CallBackCol funct);
};