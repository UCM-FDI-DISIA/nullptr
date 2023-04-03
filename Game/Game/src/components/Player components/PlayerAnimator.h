#pragma once
#include "../General Components/CharacterAnimator.h"
#include "../Card Components/CardComponent.h"

class PlayerAnimator : public CharacterAnimator {
private:
	CardComponent* cardComp_;
public:
	// Constructora
	PlayerAnimator(int _w, int _h, int _r, int _c);
	void initComponent() override;
};
