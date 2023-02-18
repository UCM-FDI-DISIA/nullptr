#include "BattleNode.h"
#include "../core/PlayerData.h"

BattleNode::BattleNode() : Node(), type(battleType(rand() % 3)) {}

void BattleNode::loadNode() const {

}