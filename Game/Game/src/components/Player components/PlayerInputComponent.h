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

	bool canAttack;
	bool canMove;

public:
	static constexpr cmpId_type id = _PLAYERINPUT;
	PlayerInputComponent() : gmCtrl_(gmCtrl()), plMovement_(nullptr), crdComp_(nullptr), prtlComp_(nullptr), canAttack(true), canMove(true) {}
	void initComponent() override;
	void handleInput() override;
	void setPortalComponent(ChargedPortalComponent* prtlC);

	inline bool getCanAttack() { return canAttack; }
	inline void setCanAttack(bool value) { canAttack = value; }
	inline bool getCanMove() { return canMove; }
	inline void setCanMove(bool value) { canMove = value; }
};

