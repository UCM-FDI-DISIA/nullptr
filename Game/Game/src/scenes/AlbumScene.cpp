#include "AlbumScene.h"
#include "../core/SDLApplication.h"

const int ALB_CARD_W = 58 * PIXEL_WIDTH;
const int ALB_CARD_H = 93 * PIXEL_HEIGHT;
const int ALB_CARD_X[3] = {90, 265, 440};
const int ALB_CARD_Y = 275;

AlbumScene::AlbumScene() : cardsByRow(2) {
	auto const& foundCards = Album::instance()->getFoundCardsByTime();
	auto const& cards = cardsData().getCardsByTime();

	for (int i = 0; i < 3; ++i) {
		int j = 0;
		auto it = foundCards[i].begin();
		for (CardData cData : cards[i]) {
			Vector2D pos;
			pos = Vector2D(ALB_CARD_X[i] + 50*(j%2) + ALB_CARD_W * (j % cardsByRow) + ALB_CARD_W * cardsByRow * i, (ALB_CARD_H + 10) * (j / cardsByRow) + ALB_CARD_Y);
			

			createCard(cData, pos, *it);

			++it; ++j;
		}
	}
	
	GameObject* bg = addGameObject();
	bg->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	bg->addComponent<Image>(&sdlutils().images().at("Album"))->attachToCamera();

	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::newScene<MainMenuScene>(); }, SDLApplication::instance(), Vector2D(10, 10), aI);


	camTr = camera->getComponent<Transform>();
}

void AlbumScene::createCard(CardData myData, Vector2D pos, bool found) {
	GameObject* card = addGameObject();
	card->addComponent<Transform>(pos, VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	card->addComponent<Image>(found ? myData.texture : &sdlutils().images().at("CardReverse"));
}

void AlbumScene::handleInput() {
	GameState::handleInput();
	if (ih().mouseWheelDown()) {
		camTr->setY(camTr->getY() + 20);
	}
	else if (ih().mouseWheelUp()) {
		camTr->setY(camTr->getY() - 20);
	}
}