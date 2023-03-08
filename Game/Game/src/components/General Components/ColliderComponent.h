#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../utils/Collisions.h"
#include <vector>
class GameObject;
class ColliderComponent : public Component
{
private:
	vector<GameObject*> others;
	CallBackCol funct;
	grpId myId;
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	ColliderComponent(CallBackCol myFunct, grpId list);
	virtual void update();
	void hasCollided();
};