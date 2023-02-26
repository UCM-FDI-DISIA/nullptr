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


#include <functional>
// Tipo de función que devuelve y recibe void, funciona también con funciones lambda con capturas
using CallBack = std::function<void(void)>;

#endif // !ECS_H_