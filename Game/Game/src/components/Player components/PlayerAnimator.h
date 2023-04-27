#pragma once
#include "../General Components/CharacterAnimator.h"
#include "../Card Components/CardComponent.h"
#include "../General Components/HealthComponent.h"

class PlayerAnimator : public CharacterAnimator {
private:
	CardComponent* cardComp_;
	HealthComponent* hlthComp_;
	BattleScene* btScn;
public:
	// Constructora
	PlayerAnimator(int _w, int _h, int _r, int _c);
	void initComponent() override;
	// Hace el update del padre y llama al metodo OnPlayerDies al terminar la animacion de muerte
	virtual void update();
};
