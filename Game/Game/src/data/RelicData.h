#pragma once
#include <string>
using namespace std;

// Reliquias
struct Relic {
public:
	string description, era;
	int health, movementVelocity, cadency, mana, attack;
	// Constructora
	Relic(string description_ = "", string era_ = "", int health_ = 0, int movementVelocity_ = 0, int cadency_ = 0, int mana_ = 0, int attack_ = 0) :
		description(description_), era(era_), health(health_), movementVelocity(movementVelocity_), cadency(cadency_), mana(mana_), attack(attack_) {}
};