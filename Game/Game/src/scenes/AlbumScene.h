#pragma once

#include "GameState.h"
#include "../data/Album.h"

class AlbumScene : public GameState {
private:
	int cardsByRow;
	Transform* camTr;
public:
	AlbumScene();
	void createCard(CardData myData, Vector2D pos, bool found);
	void handleInput() override;
};
