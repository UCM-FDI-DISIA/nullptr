#include "Player.h"
#include "../../core/SDLApplication.h"

// Crea los componentes del jugador
void Player::initGameObject() {
	transform = addComponent<Transform>(Constant::getVector2D("PLAYER_INITIAL_POSITION"), Constant::getVector2D("PLAYER_INITIAL_VELOCITY"), Constant::getFloat("PLAYER_INITIAL_WIDTH"), Constant::getFloat("PLAYER_INITIAL_HEIGHT"), Constant::getInt("PLAYER_INITIAL_ROTATION"));
	playerMovementComponent = addComponent<PlayerMovementComponent>();
	cardComponent = addComponent<CardComponent>();

	animator = addComponent<PlayerAnimator>(Constant::getInt("PLAYER_SPRITE_WIDTH"), Constant::getInt("PLAYER_SPRITE_HEIGHT"), Constant::getInt("PLAYER_SPRITE_ROWS"), Constant::getInt("PLAYER_SPRITE_COLS"));

	//Lo buscaria con getComponent, pero como pueden ser varios componentes, todos heredados de Image, termino antes pasandoselo
	//por la constructora
	effectController = addComponent<EffectController>(animator);
	health = addComponent<HealthComponent>(PlayerData::instance()->getMaxHP(), true);
}