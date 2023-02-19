#pragma once
#include "../../core/SDLApplication.h"
#include "../../core/GameObject.h"

class HandUI : public GameObject
{
private:
	// Puntero al juego
	SDLApplication* game = nullptr;

	// Puntero al componente de cartas del jugador
	CardComponent* cardComp = nullptr;

	// Deque con la mano del jugador e iterador con la carta activa
	deque<GameObject*> handUI;
	deque<Card*> handPlayer;
	deque<GameObject*>::iterator active;

public:
	// Constructora
	virtual void initGameObject(SDLApplication* _g, CardComponent* _cComp);

	// Métodos virtuales
	virtual void render() const;

	// Cambiar de selección (llamado SIEMPRE por BattleScene)
	void changeSelected(bool key, int number);

	// Descartar una carta
	void discard(deque<Card*>::iterator discarded);
};

