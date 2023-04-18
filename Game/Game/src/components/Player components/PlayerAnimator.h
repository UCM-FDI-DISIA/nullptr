#pragma once
#include "../General Components/CharacterAnimator.h"

class PlayerAnimator : public CharacterAnimator {
private:
	double startTime, elapsedTime;
public:
	// Constructora
	PlayerAnimator(int _w, int _h, int _r, int _c);
	// Hace el update del padre y llama al metodo OnPlayerDies al terminar la animacion de muerte
	virtual void update();
};
