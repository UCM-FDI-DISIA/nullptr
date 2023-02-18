#pragma once

#include "../../components/CardComponent.h"
#include "../../core/GameObject.h"
#include "../../components/Animator.h"
#include "../../core/SDLApplication.h"

class CardCounter : public GameObject {
private:
	//Referencias a mis objetos "numero" y a las cartas del jugador
	GameObject* decenas;
	GameObject* unidades;
	CardComponent* myData;

	//Me indica si debo contar mazo o descartes
	bool amIDeck;

	//El numero de cartas del vector que debo mirar
	int currentNumber;
public: 

	virtual void update();
	virtual void render() const;
	virtual void initGameObject(SDLApplication* game, bool _ref, CardComponent* _data);

	void createAnims(Animator* &_anim);
};