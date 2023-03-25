#pragma once

#include "GameState.h"
#include "../data/Album.h"

class AlbumScene : public GameState {
private:
	int cardsByRow;
public:
	AlbumScene();
	void createCard(CardData myData);
};
