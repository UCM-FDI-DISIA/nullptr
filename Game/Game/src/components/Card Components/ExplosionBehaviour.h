#pragma once
#include "../Component.h"
#include "../../core/SDLApplication.h"

class ExplosionBehaviour :  public Component
{
private:
    //Duracion del gObj
    float lifeSpan;
    float currentLifeDuration;
    BattleScene* scene;
    int damage;
    Transform* tr;
public:
    //Constructora. Determina el tick global en el que el gObj muere
    ExplosionBehaviour(int dmg, BattleScene* where, float lifeSpan) : lifeSpan(lifeSpan), currentLifeDuration(0), scene(where), damage(dmg), tr(nullptr) {}
    static const int id = _EXPLOSION_BEHAVIOUR;
    //Checkea que haya pasado el tiempo establecido, y elimina el gObj en caso positivo
    void update();
    void initComponent();
};