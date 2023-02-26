#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/MeleeEnemy.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../node/BattleNode.h"
#include "../gameObjects/UI/HandUI.h"

class HandUI;
class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor, *decs,*vida, *barraVida, *mana, *barraMana;
	vector<GameObject*> enemies;
	battleType type;
	GameObject* deck;
	GameObject* pile;
	// Puntero a la mano del jugador en la UI
	HandUI* hand = nullptr;
public:
	// Constructora
	BattleScene(battleType t_);
	static void mainMenu();
	//Metodos virtuales
	virtual void update();
	// Comunicar cambios a la UI
	void changeUISelected(bool key, int number);
	void discardUI(deque<Card*>::iterator discarded);
	void recreateUI();
	vector<GameObject*>* getEnemies();
	Player* getPlayer() { return player; };

	void createLifeBar();
	void createManaBar();
	void OnPlayerDies();
	/*void deleteEnemy(vector<GameObject*>::iterator _it) {
		if (enemies.size() == 1) enemies.erase(enemies.begin());
		else enemies.erase(prev(enemies.end())); 
	}*/
};

#endif