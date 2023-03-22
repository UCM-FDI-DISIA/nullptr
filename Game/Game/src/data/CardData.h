#pragma once
#include "../sdlutils/Texture.h"

struct CardData {
    std::string name;
    std::string attackText;
    std::string abilityText;
    int damage;
    int maxUses;
    int mana;
    int downTime;
    Texture* texture;
};