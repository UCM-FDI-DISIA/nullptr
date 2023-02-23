#include "BattleNode.h"
#include "../core/SDLApplication.h"

BattleNode::BattleNode(Vector2D const& pos) : Node(BATTLE_NODE_TEXTURE_KEY, pos), type(battleType(SDLUtils::instance()->rand().nextInt(0, 3))) {}

CallBack BattleNode::loadNode() const {
	return [&]() { 
		SDLApplication::newScene<BattleScene>(type);
	};
}