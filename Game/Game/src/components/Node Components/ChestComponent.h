#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../data/PlayerData.h"
#include "../../data/RelicData.h"
#include "../../core/SDLApplication.h"
#include "../../gameObjects/GameObject.h"
#include <list>
#include <string>

class ChestComponent :public Component {
private:
	Transform* spawnPos;
public:
	static const int id = _CHEST_COMPONENT;

	void initComponent();
	void gacha();

};