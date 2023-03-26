#include "AlbumScene.h"
#include "../core/SDLApplication.h"

const int ALB_CARD_W = 58 * PIXEL_WIDTH;
const int ALB_CARD_H = 93 * PIXEL_HEIGHT;
const int ALB_CARD_X[3] = {90, 265, 440};
const int ALB_CARD_Y = 275;

const Animation UNSELECTED_CARD_ANIM(0, 0, 1, -1);
const Animation SELECTED_CARD_ANIM(1, 2, 2, -1);
const Animation CLICKED_CARD_ANIM(3, 3, 1, -1);

AlbumScene::AlbumScene() : cardsByRow(2), camTr(nullptr), selected(false) {
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
	addGameObject<Button>([&]() { if (!selected) SDLApplication::newScene<MainMenuScene>(); }, SDLApplication::instance(), Vector2D(10, 10), aI);


	camTr = camera->getComponent<Transform>();
}

void AlbumScene::createCard(CardData myData, Vector2D pos, bool found) {
	GameObject* card = addGameObject();
	card->addComponent<Transform>(pos, VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	card->addComponent<Image>(found ? myData.texture : &sdlutils().images().at("CardReverse"));

	Button* b = addGameObject<Button>([&, cD=myData, f=found]() { if (f && !selected) selectCard(cD); }, nullptr, pos,	AnimatorInfo("CardSelection", ALB_CARD_W, ALB_CARD_H, myData.texture->width(), myData.texture->height(), 1, 4));
	Animator* a = b->getComponent<Animator>();
	a->createAnim(ONOUT, UNSELECTED_CARD_ANIM);
	a->createAnim(ONOVER, SELECTED_CARD_ANIM);
	a->createAnim(ONCLICK, CLICKED_CARD_ANIM);
	a->play(ONOUT);
	a->dettachFromCamera();
}

void AlbumScene::handleInput() {
	GameState::handleInput();
	if (ih().mouseWheelDown()) {
		camTr->setY(camTr->getY() - 20);
	}
	else if (ih().mouseWheelUp()) {
		camTr->setY(camTr->getY() + 20);
	}
}


void AlbumScene::selectCard(CardData cData) {
	selected = true;
	// FONDO
	GameObject* g = addGameObject();
	g->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	g->addComponent<Image>(SDLApplication::getTexture("CardSelectedMenu"));
	mierdon.push_back(g);
	// CARTA
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(100, 70), VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	g->addComponent<Image>(cData.texture);
	mierdon.push_back(g);
	// NOMBRE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 70), VECTOR_ZERO);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.name);
	mierdon.push_back(g);
	// ATAQUE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 100), VECTOR_ZERO, 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.attackText, true);
	mierdon.push_back(g);
	// HABILIDAD
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 150), VECTOR_ZERO, 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL16"), cData.abilityText, true);
	mierdon.push_back(g);


	// BOTÓN SALIR
	AnimatorInfo aI = AnimatorInfo(EXIT);
	g = addGameObject<Button>([&]() { deselectCard(); }, SDLApplication::instance(), Vector2D(700, 500), aI);
	mierdon.push_back(g);
}

void AlbumScene::deselectCard() {
	selected = false;
	for (auto& m : mierdon) {
		m->setAlive(false);
	}
	mierdon.clear();
}
