#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_IMAGE,
	_PLAYERMOVEMENTCOMPONENT,
	_CARDCOMPONENT,
	_HEALTH,
	_CAMERACOMPONENT,
	_BUTTON,
	_ANIMATOR,
	_PLAYER_ANIMATOR,
	_MELEE_BEHAVIOUR,
	_RANGE_BEHAVIOR,
	_COLLIDER_COMPONENT,
	_BULLET_COMPONENT,
	_SWORD_BEHAVIOUR,
	_LIFETIME,
	_MANA_BAR_COMPONENT,
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

	_LAST_GRP_ID
};
constexpr grpId_type maxGroupId = _LAST_GRP_ID;

#include <functional>
// Tipo de función que devuelve y recibe void, funciona también con funciones lambda con capturas
using CallBack = std::function<void(void)>;
class GameObject;
using CallBackCol = std::function<void(GameObject*)>;

#endif // !ECS_H_