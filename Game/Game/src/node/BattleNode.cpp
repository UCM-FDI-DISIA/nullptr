#include "BattleNode.h"
#include "../core/PlayerData.h"

list<battleType> BattleNode::battleTypes = list<battleType>();
list<battleType>::iterator* BattleNode::lastType = nullptr;

BattleNode::BattleNode(Vector2D const& pos) : Node(BATTLE_NODE_TEXTURE_KEY, pos), type(battleTypes.insert(battleTypes.end(), battleType(SDLUtils::instance()->rand().nextInt() % 3))) {}

CallBack* BattleNode::loadNode() const {
	return []() { 
		SDLApplication::newScene<BattleScene>(*(*lastType));
	};
}