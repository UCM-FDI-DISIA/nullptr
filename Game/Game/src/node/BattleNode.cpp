#include "BattleNode.h"
#include "../core/PlayerData.h"

BattleNode::BattleNode(Vector2D const& pos) : Node("Presente", pos), type(battleType(rand() % 3)) {}

CallBack* BattleNode::loadNode() const {
	return (*A::instance())(type);
}