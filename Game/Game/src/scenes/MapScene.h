#pragma once
#ifndef MAPSCENE_H_
#define MAPSCENE_H_

#include "GameState.h"

class Node;
class GameState;
class SDLApplication;

class MapScene : public GameState {
private:
	vector<Node*> const& nodeMap;
public:
	MapScene();
};

#endif