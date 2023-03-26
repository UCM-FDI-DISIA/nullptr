#pragma once
#include <string>
#include "../sdlutils/Texture.h"
using namespace std;

// Reliquias
struct Relic {
public:
	Texture* texture;
	string description, era;
	int health, mana;

	float attackMult, cadencyMult, movementVelocity;
	// Constructora
	Relic(Texture* txt, string description_ = "", string era_ = "", int health_ = 0, float movementVelocity_ = 0, float cadencyMult_ = 0, int mana_ = 0, float attackMult_ = 0.0f) :
		texture(txt), description(description_), era(era_), health(health_), movementVelocity(movementVelocity_), cadencyMult(cadencyMult_), mana(mana_), attackMult(attackMult_) {}
};
