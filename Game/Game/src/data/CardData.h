#pragma once
#include "../sdlutils/Texture.h"

enum CardTime { _CardPast, _CardPresent, _CardFuture };

struct CardData {
    std::string name;
    std::string key;
    std::string attackText;
    std::string abilityText;
    int damage;
    int maxUses;
    int mana;
    int downTime;
    Texture* texture;
    CardTime time;
};