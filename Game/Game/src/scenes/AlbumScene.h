#pragma once

#include "GameState.h"
#include "../data/Album.h"

class AlbumScene : public GameState {
private:
	int cardsByRow;
	Transform* camTr;
	int camYLimit;
	vector<GameObject*> infoWindow;
	bool selected;
public:
	AlbumScene();
	void createCard(CardData myData, Vector2D pos, bool found);
	void handleInput() override;
	void selectCard(CardData cData);
	void deselectCard();
};
