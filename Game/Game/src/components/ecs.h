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
	_RANGE_BEHAVIOUR,
	_TANK_BEHAVIOUR,
	_COLLIDER_COMPONENT,
	_BULLET_COMPONENT,
	_SWORD_BEHAVIOUR,
	_LIFETIME,
	_MANA_BAR_COMPONENT,
	_EXPLOSION_BEHAVIOUR,
	_ENEMY_GEN,
	// ... (compoment ids)

	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;


// Animaciones
struct Animation {
	int startFrame, endFrame;
	int frameRate;
	int repeat;
	Animation() : startFrame(0), endFrame(0), frameRate(0), repeat(0) {}
	Animation(int _s, int _e, int _rate, int _rep) : startFrame(_s), endFrame(_e), frameRate(_rate), repeat(_rep) {}
};


#include <functional>
// Tipo de funci�n que devuelve y recibe void, funciona tambi�n con funciones lambda con capturas
using CallBack = std::function<void(void)>;
using BoolCallBack = std::function<bool(void)>;

#endif // !ECS_H_