#include "Mana.h"
#include "../../core/SDLApplication.h"
#include "../../components/ecs.h"

void Mana::initGameObject(Vector2D pos){
	addComponent<Transform>(pos + (Vector2D(1, 0).rotate(rand() % 360) * Constant::getFloat("MANA_OFFSET")), Vector2D(), Constant::getInt("MANA_H"), Constant::getInt("MANA_W"), 0);
	ColliderComponent* collider= addComponent<ColliderComponent>( _grp_PLAYER);
	collider->addFunction(pickMana());
	addComponent<Animator>(SDLApplication::getTexture(Constant::getString("MANA_NAME")), Constant::getInt("MANA_W"), Constant::getInt("MANA_H"), 1, Constant::getInt("MANA_COLUMS"));
}

CallBackCol Mana::pickMana(){
	
	return[&](GameObject* gameobject) {
		
		PlayerData* pD = PlayerData::instance();
		if (pD->getCurrMana()+Constant::getInt("MANA_VALUE") <= pD->getMaxMana()) {
			dynamic_cast<BattleScene*>(gStt)->onManaChanges(pD->getCurrMana() + Constant::getInt("MANA_VALUE"));
			pD->setCurrMana(pD->getCurrMana() + Constant::getInt("MANA_VALUE"));
		}
		
		else {
			pD->setCurrMana(pD->getMaxMana());
		}
		setAlive(false);
	};
}