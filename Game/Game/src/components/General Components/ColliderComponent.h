#pragma once
#include "../General Components/Transform.h"
#include "../../utils/Collisions.h"
#include <vector>
class GameObject;
class ColliderComponent : public Component
{
private:
	vector <CallBackCol> functions;
	vector <CallBackExpl> otherfncts;
	grpId target;
public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	ColliderComponent(grpId list);
	virtual void update();
	void hasCollided();
	void addFunction(CallBackCol funct);
	void addFunction(CallBackExpl funct);
};