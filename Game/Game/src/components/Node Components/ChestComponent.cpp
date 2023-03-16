#include "ChestComponent.h"

void ChestComponent::initComponent() {
	spawnPos = gObj->getComponent<Transform>();
}

void ChestComponent::gacha() {
	std::vector<std::string> aux = PlayerData::instance()->getAvailableItems();

	int Rand = rand()%aux.size();

	//Hacer cosas del mapa de reliquias to guapas
	int item = PlayerData::instance()->getRelic(aux[Rand]);
	//Asignarsela al jugador
	//Assign item (añadir al jugador, añadir sprite a la escena y vivir feliz)
	//Borrar del vector
	auto it = aux.begin();
	std::advance(it, Rand);
	aux.erase(it);

	//Setear la nueva lista de items a player data
	PlayerData::instance()->setAvailableItems(aux);
}