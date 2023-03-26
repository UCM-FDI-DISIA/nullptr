#pragma once
#include "../../components/General Components/TextComponent.h"
#include "../GameObject.h"
#include "../../data/PlayerData.h"

class InventoryScene;
class InventoryCard : public GameObject {
private:
	InventoryScene* scene;
	InventoryInfo* cardData;
	GameObject* text;
	GameObject* frame;
	GameObject* deckCard;
	GameObject* deckNumber;
public:
	virtual void initGameObject(InventoryScene* s, InventoryInfo* cd, int posL, int posD = -1);
	
	/*virtual void update();
	virtual void render() const;
	virtual void handleInput();*/

	void OnDeckNumberChanges();
};