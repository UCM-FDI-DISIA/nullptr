#pragma once
#include "../Component.h"
#include "../../core/GameControl.h"

#include "PlayerMovementComponent.h"
#include "../Card Components/CardComponent.h"

class ChargedPortalComponent;
class PlayerInputComponent : public Component {
private:
	GameControl& gmCtrl_;

	PlayerMovementComponent* plMovement_;
	CardComponent* crdComp_;
	ChargedPortalComponent* prtlComp_;

	bool tutorial;
	bool canAttack;
	bool canUseAbility;
	bool canMove;
	bool canExit;

public:
	static constexpr cmpId_type id = _PLAYERINPUT;
	PlayerInputComponent(bool tuto) : gmCtrl_(gmCtrl()), plMovement_(nullptr), crdComp_(nullptr), prtlComp_(nullptr), 
		tutorial(tuto), canAttack(true), canMove(true), canUseAbility(true), canExit(true) {}
	void initComponent() override;
	void handleInput() override;
	void setPortalComponent(ChargedPortalComponent* prtlC);

	inline bool getCanAttack() { return canAttack; }
	inline void setCanAttack(bool value) { canAttack = value; }
	inline bool getCanUseAbility() { return canUseAbility; }
	inline void setCanUseAbility(bool value) { canUseAbility = value; }
	inline bool getCanMove() { return canMove; }
	inline void setCanMove(bool value) { canMove = value; }
	inline bool getCanExit() { return canExit; }
	inline void setCanExit(bool value) { canExit = value; }
};

