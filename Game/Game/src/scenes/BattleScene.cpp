#include "BattleScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/MeleeEnemy.h"


BattleScene::BattleScene(SDLApplication* _game) : GameState(_game) {
	player = new Player(game);
	stateScene.push_back(player);
	stateScene.push_back(new RangedEnemy(game, Vector2D(0,0),Vector2D(1,1),100,static_cast<Player*> (player)));
	stateScene.push_back(new MeleeEnemy(game, Vector2D(0,10), Vector2D(0,3),100, static_cast<Player*>(player)));
}