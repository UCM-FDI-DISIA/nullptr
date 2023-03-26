#pragma once

#include "../GameObject.h"
#include "../../scenes/InventoryScene.h"

class CardNumberButton : public GameObject {
private:
	InventoryInfo card;
	Transform* tr;
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(Vector2D _pos, InventoryInfo* _c);

	//Comprobar si el raton esta por encima
	virtual void update();
	//Controlar si se ha pulsado sobre el boton
	virtual void handleInput();
	// Si se pulsa el botón hay que cambiar el numero de cartas en el mazo
	void changeNumber();
};