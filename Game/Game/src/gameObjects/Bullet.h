#pragma once
#include "../core/GameObject.h"
class Bullet:public GameObject
{
private:
	int damage;
public:
	Bullet();
	~Bullet();
};
