#include "../Game/src/gameObjects/Player Object/Mana.h"
#include "../Game/src/core/SDLApplication.h"

Mana::Mana(Vector2D pos){
	addComponent<Transform>(pos + (Vector2D(1, 0).rotate(rand() % 360) * MANA_OFFSET), VECTOR_ZERO, MANA_H, MANA_W, 0);
	addComponent<ColliderComponent>(pickMana(), _grp_PLAYER);
	addComponent<Animator>(SDLApplication::getTexture(MANA_NAME), MANA_W, MANA_H, 1, MANA_COLUMS);
}

CallBack Mana::pickMana(){
	PlayerData* pD = PlayerData::instance();
	pD->setCurrMana(pD->getCurrMana() + MANA_VALUE);
	return[&]() {
	};
}