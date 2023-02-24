#pragma once

#include "../../components/Card Components/CardComponent.h"
#include "../GameObject.h"
#include "../../components/General Components/Animator.h"
#include "../../core/SDLApplication.h"

class CardCounter : public GameObject {
private:
	//Referencias a mis objetos "numero" y a las cartas del jugador
	GameObject* decs;
	GameObject* unids;
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
	}
	//Sobrescribimos los metodos
	virtual void update();
	virtual void render() const;
	virtual void initGameObject(bool _ref, CardComponent* _data);
	//Metodo para crear las animaciones de los numeros de los digitos
	void createAnims(Animator* &_anim);
	void showShuffle();
};