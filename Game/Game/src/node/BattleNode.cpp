#include "BattleNode.h"
#include "../core/PlayerData.h"

BattleNode::BattleNode() : Node("Presente"), type(battleType(rand() % 3)) {}

CallBack* BattleNode::loadNode() const {
	if (type == _PASTBATTLE) return MapScene::pasado;
	if (type == _PRESENTBATTLE) return MapScene::presente;
	return MapScene::futuro;
}