#pragma once

#include "../../components/CardComponent.h"
#include "../../core/GameObject.h"
#include "../../components/Animator.h"
#include "../../core/SDLApplication.h"

class CardCounter : public GameObject {
private:
	//Referencias a mis objetos "numero" y a las cartas del jugador
	GameObject* decs;
	GameObject* unids;
	GameObject* cards;
	CardComponent* myData;

	//Me indica si debo contar mazo o descartes
	bool amIDeck;

	//El numero de cartas del vector que debo mirar
	int currentNumber;
public:
	virtual ~CardCounter() {
		GameObject::~GameObject();
		delete(decs);
		delete(unids);
		delete(cards);
	}
	//Sobrescribimos los metodos
	virtual void update();
	virtual void render() const;
	virtual void initGameObject(bool _ref, CardComponent* _data);
	//Metodo para crear las animaciones de los numeros de los digitos
	void createAnims(Animator* &_anim);
};