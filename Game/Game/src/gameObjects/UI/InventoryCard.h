#pragma once
#include "../../components/General Components/TextComponent.h"
#include "../GameObject.h"
#include "../../data/PlayerData.h"

enum CardState {
	OUT, OVER, CLICKED
};

class InventoryScene;
class InventoryCard : public GameObject {
private:
	int posLib, posDeck;
	CardState st;
	Transform* tr;

	InventoryScene* scene;
	InventoryInfo* cardData;

	// Objetos hijos
	GameObject* text;
	GameObject* frame;
	GameObject* deckCard;
	GameObject* circle;
	GameObject* deckNumber;

	// Punteros a textos
	TextComponent* t;
	TextComponent* dN;
public:
	virtual void initGameObject(InventoryScene* s, InventoryInfo* cd, int posL, int posD = -1);
	
	void createOnDeckObjects(int _pl, int _pd);

	virtual void update();
	virtual void handleInput();

	bool isOver(int mx, int my);

	void OnDeckNumberChanges();
};