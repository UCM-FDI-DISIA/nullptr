#include "PostGameScene.h"
#include "../data/PlayerData.h"
#include "../gameObjects/UI/Button.h"
#include "../core/SDLApplication.h"


PostGameScene::PostGameScene(int dmg, int mlee, int rngd, int tnk, int mny, float tm) : damage(dmg), melee(mlee), ranged(rngd), tank(tnk), money(mny), time(tm) {
	SDLApplication::popGameState();
	newCard = PlayerData::instance()->getNewCard();
	PlayerData::instance()->addMoney(money);
	addGameObject<Button>(_grp_UI, []() { SDLApplication::returnToMapScene(); }, SHOP_EXITBUTTON_POSITION, AnimatorInfo(EXIT));
}
