#pragma once
#include "../../gameObjects/GameObject.h"

class Relic {
private:
	int health, movementVelocity, cadency, mana, attack;
public:
	// Constructora
	Relic(int health_ = 0, int movementVelocity_ = 0, int cadency_ = 0, int mana_ = 0, int attack_ = 0);

	// Getters
	inline int getRelicHealth() { return health; }
	inline int getRelicMovementVelocity() { return movementVelocity; }
	inline int getRelicCadency() { return cadency; }
	inline int getRelicMana() { return mana; }
	inline int getRelicAttack() { return attack; }
	// Setters
	inline void setRelicHealth(int health_) { health = health_; }
	inline void setRelicMovementVelocity(int movementVelocity_) { movementVelocity = movementVelocity_; }
	inline void setRelicCadency(int cadency_) { cadency = cadency_; }
	inline void setRelicMana(int mana_) { mana = mana_; }
	inline void setRelicAttack(int attack_) { attack = attack_; }
};
