#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include <cmath>

struct UICard {
	GameObject* card;
	pair<GameObject*, GameObject*> manaNumber;
	pair<GameObject*, GameObject*> ammoNumber;
	//GameObject* ammoBar;
	//vector<GameObject*> ammoBlocks;
	int ammo;
	int maxAmmo;

	UICard() : card(nullptr), ammo(0), maxAmmo(INT_MAX) {};
	~UICard() {
		delete card;
		delete manaNumber.first;
		delete manaNumber.second;
		delete ammoNumber.first;
		delete ammoNumber.second;
		//delete ammoBar;
		//for (int i = 0; i < maxAmmo; i++) delete ammoBlocks[i];
	}
};

class HandUI : public GameObject
{
private:
	// Puntero al componente de cartas del jugador
	CardComponent* cardComp = nullptr;

	// Deque con la mano del jugador e iterador con la carta activa
	deque<UICard*> handUI;
	deque<Card*> handPlayer;
	deque<UICard*>::iterator active;

public:
	// Constructora
	virtual void initGameObject(CardComponent* _cComp);
	virtual ~HandUI();
	// Métodos virtuales
	virtual void render() const;

	// Crear o recrear la UI
	void createUI();
	void createCard(int i, int posX, int posY, int rotation);

	// Cambiar de selección (llamado SIEMPRE por BattleScene)
	void changeSelected(bool key, int number);
	void repositionSelected(int cardPos, int offset);

	// Descartar una carta
	void discard(deque<Card*>::iterator discarded);

	// Cambiar la munición de una carta
	void changeAmmo(deque<Card*>::iterator used);

	// Reposiciona las cartas según el número de cartas que quedan en la mano
	void rearrangeThree();
	void rearrangeTwo();
	void rearrangeOne();
	void rearrangeCard(deque<UICard*>::iterator it, int cardPos, int rotation,
		tuple<int, int, int, float> ammoPos, tuple<int, int, int, int> manaPos);

	// Buscar la carta recibida del cardComp en la mano de la UI
	deque<UICard*>::iterator searchCard(deque<Card*>::iterator searched);

	GameObject* createNumber(Vector2D pos, float rotation, int value, char type);
	void createNumberAnims(GameObject* obj, int value, char type);
};

