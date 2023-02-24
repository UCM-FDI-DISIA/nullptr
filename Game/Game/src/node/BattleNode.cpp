#include "BattleNode.h"
#include "../core/SDLApplication.h"

// Constructora, recibe posición del nodo en el mapa
BattleNode::BattleNode(Vector2D const& pos) : Node(BATTLE_NODE_TEXTURE_KEY, pos), type(battleType(SDLUtils::instance()->rand().nextInt(0, 3))) {}

// Devuelve un CallBack que abre la escena de batalla del tipo del nodo
CallBack BattleNode::loadNode() const {
	return [&]() { 
		SDLApplication::newScene<BattleScene>(type);
	};
}