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
			pos = Vector2D(ALB_CARD_X[i] + 50*(j%2) + ALB_CARD_W * (j % cardsByRow) + ALB_CARD_W * cardsByRow * i, (ALB_CARD_H + ALB_CARD_Y_DIST) * (j / cardsByRow) + ALB_CARD_Y);
			

			createCard(cData, pos, *it);

			if (j/2 > camYLimit) camYLimit = j/2;

			++it; ++j;
		}
	}
	//camYLimit -= 1;
	camYLimit *= (ALB_CARD_H + ALB_CARD_Y_DIST);
	camYLimit -= ALB_CARD_H / 2;

	GameObject* bg = addGameObject();
	bg->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	bg->addComponent<Image>(SDLApplication::getTexture("Album"))->attachToCamera();

	AnimatorInfo aI = AnimatorInfo(EXIT);
	exitButton = addGameObject<Button>([&]() { if (!selected) SDLApplication::newScene<MainMenuScene>(); }, Vector2D(10, 10), aI);
	exitButton->setAsDefaultButton();

	camTr = camera->getComponent<Transform>();
	GameObject* found = addGameObject();
	found->addComponent<Transform>(FOUND_TEXT_POS, VECTOR_ZERO, 50, 24);
	found->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_BOLD38"), to_string(Album::instance()->getFoundCards().size()) 
		+ "/"+ to_string(CardsDataContainer::instance()->numOfCards()))->attachToCamera();
}

void AlbumScene::createCard(CardData myData, Vector2D pos, bool found) {
	GameObject* card = addGameObject();
	card->addComponent<Transform>(pos, VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	card->addComponent<Image>(found ? myData.texture : SDLApplication::getTexture("CardReverse"));

	Button* b = addGameObject<Button>([&, cD=myData, f=found]() { if (f && !selected) selectCard(cD); }, pos, AnimatorInfo("CardSelection", ALB_CARD_W, ALB_CARD_H, myData.texture->width(), myData.texture->height(), 1, 4));
	b->getComponent<ButtonComponent>()->setOnSelected(
		[&](Transform* myTr) {
			if (myTr->getY() > ALB_CARD_H * 2) camTr->setY(-myTr->getY() + ALB_CARD_H * 2);
			else camTr->setY(0);
		});
	Animator* a = b->getComponent<Animator>();
	a->createAnim(ONOUT, UNSELECTED_CARD_ANIM);
	a->createAnim(ONOVER, SELECTED_CARD_ANIM);
	a->createAnim(ONCLICK, CLICKED_CARD_ANIM);
	a->play(ONOUT);
	a->dettachFromCamera();

	// Añadir nº si es una carta encontrada
	if (found) {
		Transform* tr = b->getComponent<Transform>();
		Vector2D decsPos = Vector2D(tr->getPos().getX() + 10, tr->getPos().getY() + 13);
		createNumber(addGameObject(), decsPos, myData.maxUses / 10, 'a');
		createNumber(addGameObject(), decsPos + Vector2D(10, 0), myData.maxUses % 10, 'a');
		createNumber(addGameObject(), decsPos + Vector2D(3, 31), myData.mana / 10, 'm');
		createNumber(addGameObject(), decsPos + Vector2D(14, 31), myData.mana % 10, 'm');
	}
}

void AlbumScene::handleInput() {
	GameState::handleInput();
	if (!selected) {
		// Scroll
		camTr->setY(camTr->getY() - 20 * gmCtrl_.scroll(false));
		if (camTr->getY() < -camYLimit) camTr->setY(-camYLimit);
		else if (camTr->getY() > 0) camTr->setY(0);
		// Atrás
		if (gmCtrl_.goBack()) {
			exitButton->setAsCurrentButton();
		}
	}
}


void AlbumScene::selectCard(CardData cData) {
	selected = true;
	// FONDO
	GameObject* g = addGameObject();
	g->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, WIN_WIDTH, WIN_HEIGHT);
	g->addComponent<Image>(SDLApplication::getTexture("CardSelectedMenu"))->attachToCamera();
	infoWindow.push_back(g);
	// CARTA
	g = addGameObject();
	Transform* tr = g->addComponent<Transform>(Vector2D(100, 70), VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	g->addComponent<Image>(cData.texture)->attachToCamera();
	infoWindow.push_back(g);
	// NOMBRE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 70), VECTOR_ZERO);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR22"), cData.name)->attachToCamera();
	infoWindow.push_back(g);
	// ATAQUE
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 100), VECTOR_ZERO, 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR22"), cData.attackText, true)->attachToCamera();
	infoWindow.push_back(g);
	// HABILIDAD
	g = addGameObject();
	g->addComponent<Transform>(Vector2D(300, 150), VECTOR_ZERO, 200);
	g->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR22"), cData.abilityText, true)->attachToCamera();
	infoWindow.push_back(g);

	// TO DO -> QUE SE MUESTREN MANÁ Y MUNICIÓN EN EL POPUP

	// BOTï¿½N SALIR
	AnimatorInfo aI = AnimatorInfo(EXIT);

	Button* b = addGameObject<Button>([&]() { deselectCard(); butNavigator->unlockMovement(); butNavigator->selectDefaultButton(); }, Vector2D(700, 500), aI);
	butNavigator->lockMovement();
	b->setAsCurrentButton();
	infoWindow.push_back(b);
}

void AlbumScene::deselectCard() {
	selected = false;
	for (auto& m : infoWindow) {
		m->setAlive(false);
	}
	infoWindow.clear();
}

// Crear un número según los datos recibidos
void AlbumScene::createNumber(GameObject* number, Vector2D pos, int value, char type) {
	// Añadir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), UI_AMMO_NUMBERS_WIDTH - 1, UI_AMMO_NUMBERS_HEIGHT - 1);

	// Seleccionar textura
	Texture* txt;
	if (type == 'a') txt = SDLApplication::getTexture(STATISTICS_NUMBERS);
	else txt = SDLApplication::getTexture(CARDS_NUMBERS);

	// Añadir animator y crear animaciones
	auto anim = number->addComponent<Animator>(txt, CARDS_NUMBERS_WIDTH, CARDS_NUMBERS_HEIGHT, CARDS_NUMBERS_ROWS, CARDS_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS - 2; j++) anim->createAnim(to_string(j), j, j, 1, 0);

	// Reproducir animación correspondiente
	anim->play(to_string(value));
}