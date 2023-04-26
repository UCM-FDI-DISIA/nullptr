#include "PostGameScene.h"
#include "../data/PlayerData.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"
#include <iomanip>
#include <sstream>


PostGameScene::PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm) : damage(dmg), melee(mlee), ranged(rngd), tank(tnk), money(mny), time(tm) {

	int i = 0;

	SDLApplication::popGameState();
	newCard = PlayerData::instance()->getNewCard();
	PlayerData::instance()->addMoney(money);

	GameObject* Frame = addGameObject(_grp_UI);
	Frame->addComponent<Transform>(Vector2D(40,15),VECTOR_ZERO, 510, 690);
	Frame->addComponent<Image>(SDLApplication::getTexture("PostGameFrame"));

	GameObject* title = addGameObject(_grp_UI);
	title->addComponent<Transform>(Vector2D(60, 35), VECTOR_ZERO, 400, 100);
	title->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL48"), "ESTADISTICAS");

	GameObject* enemiesKilled = addGameObject(_grp_UI);
	enemiesKilled->addComponent<Transform>(Vector2D(60, 125), VECTOR_ZERO, 400, 100);
	enemiesKilled->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Enemigos derrotados: " + to_string(mlee + rngd + tnk));
	if (mlee > 0) {
		i++;
		GameObject* melee = addGameObject(_grp_UI);
		melee->addComponent<Transform>(Vector2D(80, 125 + 60 * i), VECTOR_ZERO, 400, 100);
		melee->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Melee: " + to_string(mlee));
	}
	if (rngd > 0) {
		i++;
		GameObject* ranged = addGameObject(_grp_UI);
		ranged->addComponent<Transform>(Vector2D(80, 125 + 60 * i), VECTOR_ZERO, 400, 100);
		ranged->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Ranged: " + to_string(rngd));
	}
	if (tnk > 0) {
		i++;
		GameObject* tank = addGameObject(_grp_UI);
		tank->addComponent<Transform>(Vector2D(80, 125 + 60 * i), VECTOR_ZERO, 400, 100);
		tank->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Tank: " + to_string(tnk));
	}
	GameObject* damage = addGameObject(_grp_UI);
	damage->addComponent<Transform>(Vector2D(60, 215 + 60 * i), VECTOR_ZERO, 400, 100);
	damage->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Vida perdida: " + to_string(dmg));

	GameObject* time = addGameObject(_grp_UI);
	time->addComponent<Transform>(Vector2D(60, 305 + 60 * i), VECTOR_ZERO, 400, 100);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << tm;
	std::string mystring = ss.str();
	time->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Tiempo empleado: " + mystring + " s");

	GameObject* money = addGameObject(_grp_UI);
	money->addComponent<Transform>(Vector2D(60, 395 + 180), VECTOR_ZERO, 400, 100);
	money->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL36"), "Dinero obtenido: " + to_string(mny));


	GameObject* spotlight = addGameObject(_grp_UI);
	spotlight->addComponent<Transform>(SPOTLIGHT_POSITION, VECTOR_ZERO, 300, 100);
	spotlight->addComponent<Image>(SDLApplication::getTexture("SpotLight"));

	GameObject* PlayerAnim = addGameObject(_grp_UI);
	PlayerAnim->addComponent<Transform>(CARD_CREATION_POSITION, VECTOR_ZERO, 192, 192);
	Animator* anim = PlayerAnim->addComponent<Animator>(SDLApplication::getTexture(PLAYER), PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_ROWS, PLAYER_SPRITE_COLS);
	anim->createAnim("cardCreation", Animation(PLAYER_SKILL_IDLE_INITIAL_FRAME, PLAYER_SKILL_IDLE_FINAL_FRAME, PLAYER_SKILL_IDLE_FRAME_RATE * 0.75, 1));
	anim->play("cardCreation");

	addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, POSTGAME_EXITBUTTON_POSITION, AnimatorInfo(EXIT));
}
