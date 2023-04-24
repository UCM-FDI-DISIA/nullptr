#pragma once
#include "../checkML.h"
using cmpId_type = int;
enum cmpId : cmpId_type {
	// ... (compoment ids)
	_TRANSFORM = 0,
	_IMAGE,
	_PLAYERMOVEMENTCOMPONENT,
	_POINTERCOMPONENT,
	_CARDCOMPONENT,
	_HEALTH,
	_STATUS,
	_CAMERACOMPONENT,
	_BUTTON,
	_ANIMATOR,
	_PLAYER_ANIMATOR,
	_ENEMY_BEHAVIOUR,
	_COLLIDER_COMPONENT,
	_HITBOX_DAMAGE_COMPONENT,
	_HITBOX_STATUS_COMPONENT,
	_HITBOX_EXPLOSION_COMPONENT,
	_FOLLOW_ENEMY_COMPONENT,
	_LIFETIME,
	_BAR_COMPONENT,
	_ENEMY_GEN,
	_CHEST_COMPONENT,
	_ETER,
	_ON_DEATH,
	_CHARGED_PORTAL,
	_CALLBACK_DELAYER,
	// ... (compoment ids)

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
using grpId_type = int;
enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_ENEMIES,
	_grp_ENM_ATTACK,
	_grp_PLYR_ATTACK,
	_grp_PLAYER,
	_grp_RELICS,
	_grp_CARDS,
	_grp_MANA,
	_grp_UI,
	_grp_POINTER, // El puntero debe ser lo ultimo en renderizar
	// do not remove this
	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

using cardId_type = int;
enum CardId : cardId_type {
	_card_NULL=-1,
	_card_GUN = 0,
	_card_SWORD,
	_card_TORCH,
	_card_LASERGLASSES,
	_card_BOW,
	_card_PULGA,
	_card_SPEAR,
	_card_SMG,
	_card_ASSAULTRIFLE,
	_card_LIGHTRIFLE,
	_card_MEGAPHONE,
	_card_RIOTSHIELD,
	_card_RITUALAXE,
	_card_CHEATGUN,
	_card_LASERKATANA,

	// do not remove this
	_LAST_CARD_ID
};
constexpr cardId_type maxCardId = _LAST_CARD_ID;

// Animaciones
struct Animation {
	int startFrame, endFrame;
	int frameRate;
	int repeat;
	Animation() : startFrame(0), endFrame(0), frameRate(0), repeat(0), linked(false) {}
	Animation(int _s, int _e, int _rate, int _rep) : startFrame(_s), endFrame(_e), frameRate(_rate), repeat(_rep), linked(false) {}

	bool linked;
};

#include <functional>
// Tipo de funci�n que devuelve y recibe void, funciona tambi�n con funciones lambda con capturas
using CallBack = std::function<void(void)>;
class GameObject;
using CallBackCol = std::function<void(GameObject*)>;
using BoolCallBack = std::function<bool(void)>;
