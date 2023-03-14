#include "../Game/src/gameObjects/Player Object/Mana.h"
#include "../Game/src/core/SDLApplication.h"

void Mana::initGameObject(Vector2D pos){
	addComponent<Transform>(pos + (Vector2D(1, 0).rotate(rand() % 360) * MANA_OFFSET), VECTOR_ZERO, MANA_H, MANA_W, 0);
	addComponent<ColliderComponent>(pickMana(), _grp_PLAYER);
	addComponent<Animator>(SDLApplication::getTexture(MANA_NAME), MANA_W, MANA_H, 1, MANA_COLUMS);
}

CallBackCol Mana::pickMana(){
	
	return[&](GameObject* gameobject) {
		
		PlayerData* pD = PlayerData::instance();
		if (pD->getCurrMana() < pD->getMaxMana()) {
			pD->setCurrMana(pD->getCurrMana() + MANA_VALUE);
		}
		
		else {
			pD->setCurrMana(pD->getMaxMana());
		}
		setAlive(false);
	};
}

#include <functional>
// Tipo de funci�n que devuelve y recibe void, funciona tambi�n con funciones lambda con capturas
using CallBack = std::function<void(void)>;
class GameObject;
using CallBackCol = std::function<void(GameObject*)>;
using BoolCallBack = std::function<bool(void)>;