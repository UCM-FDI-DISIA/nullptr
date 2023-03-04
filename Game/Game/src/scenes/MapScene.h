#pragma once

#include "GameState.h"
#include "../gameObjects/Node Objects/Map.h"

class MapScene : public GameState {
private:
	vector<Node*> const& nodeMap;
public:
	MapScene();
};