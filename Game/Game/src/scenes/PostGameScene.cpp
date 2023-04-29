#include "PostGameScene.h"
#include "../data/PlayerData.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"
#include <iomanip>
#include <sstream>


PostGameScene::PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm) : damage(dmg), melee(mlee), ranged(rngd), tank(tnk), money(mny), time(tm), nextEvent(0), coolDown(0) {

	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << time;
	timeText = ss.str();

	SDLApplication::popGameState();
	newCard = PlayerData::instance()->getNewCard();
	PlayerData::instance()->addMoney(money);
	PlayerData::instance()->nextLevel();

	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("BattleBackground"));
	GameObject* background3 = addGameObject();
	background3->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background3->addComponent<Image>(SDLApplication::getTexture("BattleBackground3"));
	GameObject* background2 = addGameObject();
	background2->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background2->addComponent<Image>(SDLApplication::getTexture("BattleBackground2"));
	GameObject* background1 = addGameObject();
	background1->addComponent<Transform>(Vector2D(), Vector2D(), BATTLEBACKGROUND123_WIDTH, BATTLEBACKGROUND123_HEIGHT);
	background1->addComponent<Image>(SDLApplication::getTexture("BattleBackground1"));


	GameObject* Frame = addGameObject(_grp_UI);
	Frame->addComponent<Transform>(Vector2D(40,15),VECTOR_ZERO, 510, 690);
	Frame->addComponent<Image>(SDLApplication::getTexture("PostGameFrame"));

	GameObject* title = addGameObject(_grp_UI);
	title->addComponent<Transform>(Vector2D(90, 65), VECTOR_ZERO, 400, 100);
	title->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL48"), "ESTADISTICAS");
}

void PostGameScene::update()
{
	GameState::update();
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE) || coolDown > NEXT_EVENT_TIMER * (nextEvent == 7 ? 2 : 1)) {
		nextEvent++;
		showObject();
		if (nextEvent < 10) coolDown = 0;
	}
	else coolDown += SDLApplication::instance()->getDeltaTimeSeconds();
}

void PostGameScene::showObject() {

	GameObject* text;
	int i = 0;

	switch (nextEvent)
	{
	case 1:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(70, 155), VECTOR_ZERO, 400, 100);
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Enemigos derrotados: " + to_string(melee + ranged + tank));
		break;
	case 2:
		if (melee > 0) {
			i++;
			text = addGameObject(_grp_UI);
			text->addComponent<Transform>(Vector2D(90, 155 + 60 * i), VECTOR_ZERO, 400, 100);
			text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Soldados: " + to_string(melee));
		}
		if (ranged > 0) {
			i++;
			text = addGameObject(_grp_UI);
			text->addComponent<Transform>(Vector2D(90, 155 + 60 * i), VECTOR_ZERO, 400, 100);
			text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Arqueros: " + to_string(ranged));
		}
		if (tank > 0) {
			i++;
			text = addGameObject(_grp_UI);
			text->addComponent<Transform>(Vector2D(90, 155 + 60 * i), VECTOR_ZERO, 400, 100);
			text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Robustos: " + to_string(tank));
		}
		break;
	case 3:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(70, 245 + 180), VECTOR_ZERO, 400, 100);
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Vida perdida: " + to_string(damage));
		break;
	case 4:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(70, 335 + 180), VECTOR_ZERO, 400, 100);
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Tiempo empleado: " + timeText + " s");
		break;
	case 5:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(70, 425 + 180), VECTOR_ZERO, 400, 100);
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Dinero obtenido: " + to_string(money));
		break;
	case 6:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(70, 425 + 180), VECTOR_ZERO, 400, 100);
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Dinero obtenido: " + to_string(money));
		break;
	case 7:
		showPlayer();
		break;
	case 8:
		text = addGameObject(_grp_UI);
		text->addComponent<Transform>(Vector2D(
			newCard.second == 2 ? 575 : 620, 30), VECTOR_ZERO, 400, 100);
		
		text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL48"), 
			(newCard.second == 2 ? "NUEVAS CARTAS OBTENIDAS" : "NUEVA CARTA OBTENIDA"), build_sdlcolor(0xffffffff));
		showCard();
		break;
	case 9:
		addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, POSTGAME_EXITBUTTON_POSITION, AnimatorInfo(EXIT));
		break;
	}
}


void PostGameScene::showCard()
{
	if (newCard.second == 2) {
		GameObject* card = addGameObject(_grp_UI);
		card->addComponent<Transform>(NEW_CARD_POSITION - Vector2D(24,38), VECTOR_ZERO, 232, 372);
		card->addComponent<Image>(cardsData().get(Card::getCardIDfromEnum(newCard.first)).texture);
	}
	GameObject* card = addGameObject(_grp_UI);
	card->addComponent<Transform>(NEW_CARD_POSITION, VECTOR_ZERO, 232, 372);
	card->addComponent<Image>(cardsData().get(Card::getCardIDfromEnum(newCard.first)).texture);
}

void PostGameScene::showPlayer() {
	GameObject* spotlight = addGameObject(_grp_UI);
	spotlight->addComponent<Transform>(SPOTLIGHT_POSITION, VECTOR_ZERO, 300, 100);
	spotlight->addComponent<Image>(SDLApplication::getTexture("SpotLight"));
	GameObject* player = addGameObject(_grp_UI);
	player->addComponent<Transform>(CARD_CREATION_POSITION, VECTOR_ZERO, 192, 192);
	Animator* anim = player->addComponent<Animator>(SDLApplication::getTexture(PLAYER), PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_ROWS, PLAYER_SPRITE_COLS);
	anim->createAnim("cardCreation", Animation(PLAYER_SKILL_IDLE_INITIAL_FRAME + 2, PLAYER_SKILL_IDLE_FINAL_FRAME, PLAYER_SKILL_IDLE_FRAME_RATE * 0.5, 1, true));
	anim->play("cardCreation");
}