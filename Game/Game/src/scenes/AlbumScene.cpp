#include "AlbumScene.h"
#include "../core/SDLApplication.h"

//const int ALB_CARD_W = 58 * PIXEL_WIDTH;
//const int ALB_CARD_H = 93 * PIXEL_HEIGHT;
//const int ALB_CARD_X[3] = {90, 265, 440};
//const int ALB_CARD_Y = 275;
//const int ALB_CARD_Y_DIST = 10;
//
//const Animation UNSELECTED_CARD_ANIM(0, 0, 1, -1);
//const Animation SELECTED_CARD_ANIM(1, 2, 2, -1);
//const Animation CLICKED_CARD_ANIM(3, 3, 1, -1);

AlbumScene::AlbumScene() : cardsByRow(2), camTr(nullptr), camYLimit(0), selected(false) {
	auto const& foundCards = Album::instance()->getFoundCardsByTime();
	auto const& cards = cardsData().getCardsByTime();


	for (int i = 0; i < 3; ++i) {
		int j = 0;
		auto it = foundCards[i].begin();
		for (CardData cData : cards[i]) {
			Vector2D pos;
			pos = Vector2D(ALB_CARD_X[i] + 50*(j%2) + Constant::getInt("ALB_CARD_W") * (j % cardsByRow) + Constant::getInt("ALB_CARD_W") * cardsByRow * i, (Constant::getInt("ALB_CARD_H") + Constant::getInt("ALB_CARD_Y_DIST")) * (j / cardsByRow) + Constant::getInt("ALB_CARD_Y"));
			

			createCard(cData, pos, *it);

			if (j/2 > camYLimit) camYLimit = j/2;

			++it; ++j;
		}
	}
	cout << camYLimit << " ";
	camYLimit -= 1;
	camYLimit *= (Constant::getInt("ALB_CARD_H") + Constant::getInt("ALB_CARD_Y_DIST"));
	cout << camYLimit << endl;

	GameObject* bg = addGameObject();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	bg->addComponent<Image>(SDLApplication::getTexture("Album"))->attachToCamera();

	AnimatorInfo aI = AnimatorInfo(Constant::getString("EXIT"));
	addGameObject<Button>([&]() { if (!selected) SDLApplication::newScene<MainMenuScene>(); }, Vector2D(10, 10), aI);


	camTr = camera->getComponent<Transform>();
}

void AlbumScene::createCard(CardData myData, Vector2D pos, bool found) {
	GameObject* card = addGameObject();
	card->addComponent<Transform>(pos, Vector2D(), Constant::getInt("ALB_CARD_W"), Constant::getInt("ALB_CARD_H"));
	card->addComponent<Image>(found ? myData.texture : SDLApplication::getTexture("CardReverse"));

	Button* b = addGameObject<Button>([&, cD=myData, f=found]() { if (f && !selected) selectCard(cD); }, pos, AnimatorInfo("CardSelection", Constant::getInt("ALB_CARD_W"), Constant::getInt("ALB_CARD_H"), myData.texture->width(), myData.texture->height(), 1, 4));
	Animator* a = b->getComponent<Animator>();
	a->createAnim(Constant::getString("ONOUT"), Constant::getAnimation("UNSELECTED_CARD_ANIM"));
	a->createAnim(Constant::getString("ONOVER"), Constant::getAnimation("SELECTED_CARD_ANIM"));
	a->createAnim(Constant::getString("ONCLICK"), Constant::getAnimation("CLICKED_CARD_ANIM"));
	a->play(Constant::getString("ONOUT"));
	a->dettachFromCamera();
}

void AlbumScene::handleInput() {
	GameState::handleInput();
	if (ih().mouseWheelDown()) {
		if (camTr->getY() > -camYLimit) camTr->setY(camTr->getY() - 20);
	}
	else if (ih().mouseWheelUp()) {
		if (camTr->getY() < 0) camTr->setY(camTr->getY() + 20);
	}
}


void AlbumScene::selectCard(CardData cData) {
	selected = true;
	// FONDO
	GameObject* g = addGameObject();
	g->addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	g->addComponent<Image>(SDLApplication::getTexture("CardSelectedMenu"))->attachToCamera();
	infoWindow.push_back(g);
	// CARTA
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(100, 70), Vector2D(), Constant::getInt("ALB_CARD_W"), Constant::getInt("ALB_CARD_H"));
	g->addComponent<Image>(cData.texture)->attachToCamera();
	infoWindow.push_back(g);
	// NOMBRE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 70), Vector2D());
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.name)->attachToCamera();
	infoWindow.push_back(g);
	// ATAQUE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 100), Vector2D(), 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.attackText, true)->attachToCamera();
	infoWindow.push_back(g);
	// HABILIDAD
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 150), Vector2D(), 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.abilityText, true)->attachToCamera();
	infoWindow.push_back(g);


	// BOT�N SALIR
	AnimatorInfo aI = AnimatorInfo(Constant::getString("EXIT"));
	g = addGameObject<Button>([&]() { deselectCard(); }, Vector2D(700, 500), aI);
	infoWindow.push_back(g);
}

void AlbumScene::deselectCard() {
	selected = false;
	for (auto& m : infoWindow) {
		m->setAlive(false);
	}
	infoWindow.clear();
}
