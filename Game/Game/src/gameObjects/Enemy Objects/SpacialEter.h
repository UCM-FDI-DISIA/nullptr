#pragma once
#include "../GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include"../../components/Enemy components/EterBehaviour.h"
class SpacialEter :public GameObject
{

public:
	virtual void initGameObject(int x, int y);
};