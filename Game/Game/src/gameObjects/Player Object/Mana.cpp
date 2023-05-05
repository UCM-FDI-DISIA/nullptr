#include "Mana.h"
#include "../../core/SDLApplication.h"
#include "../../components/ecs.h"

void Mana::initGameObject(Vector2D pos){
	manaPickSound = &sdlutils().soundEffects().at(MANA_PICK);
	addComponent<Transform>(pos + (Vector2D(1, 0).rotate(rand() % 360) * MANA_OFFSET), VECTOR_ZERO, MANA_H, MANA_W, 0);
	ColliderComponent* collider = addComponent<ColliderComponent>( _grp_PLAYER, 5 * MANA_H, 5 * MANA_W);
	collider->addFunction(pickMana());
	addComponent<Animator>(SDLApplication::getTexture(MANA_NAME), MANA_W, MANA_H, 1, MANA_COLUMS);
}

CallBackCol Mana::pickMana(){
	
	return[&](GameObject* gameobject) {
		
		PlayerData* pD = PlayerData::instance();
		if (pD->getCurrMana()+MANA_VALUE <= pD->getMaxMana()) {
			Mix_PlayChannelTimed(-1, manaPickSound->getChunk(), 0, -1);
			dynamic_cast<BattleScene*>(gStt)->onManaChanges(pD->getCurrMana() + MANA_VALUE);
			pD->setCurrMana(pD->getCurrMana() + MANA_VALUE);
		}
		
		else {
			pD->setCurrMana(pD->getMaxMana());
		}
		setAlive(false);
	};
}