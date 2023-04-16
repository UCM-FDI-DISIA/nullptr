#pragma once
#include "../Component.h"
#include "../../core/GameControl.h"

#include "PlayerMovementComponent.h"
#include "../Card Components/CardComponent.h"

class PlayerInputComponent : public Component {
private:
	GameControl& gmCtrl_;

	PlayerMovementComponent* plMovement_;
	CardComponent* crdComp_;
public:
	static constexpr cmpId_type id = _PLAYERINPUT;
	PlayerInputComponent() : gmCtrl_(gmCtrl()), plMovement_(nullptr), crdComp_(nullptr) {}
	void initComponent() override;
	void handleInput() override;
};
