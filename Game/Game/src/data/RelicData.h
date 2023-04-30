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
	Relic(Texture* txt, string id_ = "", string description_ = "", string era_ = "", int health_ = 0, float speed_ = 0, float fireRateMult_ = 0, int mana_ = 0, float attackMult_ = 0.0f) :
		texture(txt), id(id_), description(description_), era(era_), health(health_), speed(speed_), fireRateMult(fireRateMult_), mana(mana_), attackMult(attackMult_) {}
};
