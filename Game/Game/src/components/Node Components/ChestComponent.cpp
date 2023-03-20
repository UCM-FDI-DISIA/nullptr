#include "ChestComponent.h"

void ChestComponent::initComponent() {
	spawnPos = gObj->getComponent<Transform>();
}

void ChestComponent::gacha() {
	//Sacamos el vector de reliquias disponibles
	std::vector<std::string> aux = PlayerData::instance()->getAvailableItems();

	//Sacamos un random entre 0 y su maximo
	int Rand = rand()%aux.size();

	//Sacamos la reliquia con la key que nos dan
	Relic* item = SDLApplication::instance()->getRelic(aux[Rand]);
	
	//Asignarsela al jugador
	PlayerData::instance()->addRelic(item);
	
	//Assign item (añadir sprite a la escena y vivir feliz)
	GameObject* sprite = gStt->addGameObject(_grp_GENERAL);
	sprite->addComponent<Transform>(spawnPos);
	sprite->addComponent<Image>(item->texture);
	
	
	//Borrar del vector
	auto it = aux.begin();
	std::advance(it, Rand);
	aux.erase(it);

	//Setear la nueva lista de items a player data
	PlayerData::instance()->setAvailableItems(aux);
}