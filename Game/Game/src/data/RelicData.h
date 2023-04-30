#pragma once
#include <string>
#include "../sdlutils/Texture.h"
using namespace std;

// Reliquias
struct Relic {
public:
	Texture* texture;
	string description, era, id;
	int health, mana;

	float attackMult, fireRateMult, speed;
	// Constructora
	Relic(Texture* txt, string id = "", string description_ = "", string era_ = "", int health_ = 0, float movementVelocity_ = 0, float cadencyMult_ = 0, int mana_ = 0, float attackMult_ = 0.0f) :
		texture(txt), id(id), description(description_), era(era_), health(health_), speed(movementVelocity_), fireRateMult(cadencyMult_), mana(mana_), attackMult(attackMult_) {}
};
