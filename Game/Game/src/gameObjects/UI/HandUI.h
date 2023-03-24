#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"

struct UICard {
	GameObject* card;
	pair<GameObject*, GameObject*> ammoNumber;
	vector<GameObject*> ammoBlocks;

	UICard() : card(nullptr) {};
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

	// Descartar una carta
	void discard(deque<Card*>::iterator discarded);

	// Reposiciona las cartas según el número de cartas que quedan en la mano
	void rearrangeThree();
	void rearrangeTwo();
	void rearrangeOne();

	void createNumberAnims(GameObject* obj, int value);
};

