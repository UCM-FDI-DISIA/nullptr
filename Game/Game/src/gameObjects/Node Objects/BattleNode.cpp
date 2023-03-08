#include "BattleNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posición del nodo en el mapa
BattleNode::BattleNode(Vector2D const& pos, battleType _t) : 
	Node(BATTLE_NODE_TEXTURE_KEY, pos, 
		[&]() {
			SDLApplication::newScene<BattleScene>(type);
		}), 

	type(_t) {
}