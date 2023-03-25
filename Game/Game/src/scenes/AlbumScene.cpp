#include "AlbumScene.h"
#include "../core/SDLApplication.h"

AlbumScene::AlbumScene() : cardsByRow(5) {
	auto const& cards = Album::instance()->getFoundCards();
	cardsData().numOfCards();
	createCard(cards[0]);


	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::newScene<MainMenuScene>(); }, SDLApplication::instance(), Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 50), aI);
}

void AlbumScene::createCard(CardData myData) {
	GameObject* card = addGameObject();
	card->addComponent<Transform>(Vector2D(0, 0), VECTOR_ZERO, myData.texture->width(), myData.texture->height());
	card->addComponent<Image>(myData.texture);
}