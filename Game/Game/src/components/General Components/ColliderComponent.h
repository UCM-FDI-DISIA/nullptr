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
	Transform* tr;
	float width, height;

public:
	static const int id = _COLLIDER_COMPONENT;
	//Devuelve un booleano de colision entre el objeto y el objetivo
	ColliderComponent(grpId id);
	ColliderComponent(grpId id, int width, int height);

	void initComponent() override;
	void update() override;

	void hasCollided();
	void addFunction(CallBackCol funct);
	void addFunction(CallBackExpl funct);

	Vector2D getPos();
	float getWidth();
	float getHeight();
	float getRotation();
	Vector2D getAnchorPoint();

#ifdef _DEBUG
	void render() const;
#endif
};