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
    vector<GameObject*>* target;
public:
    //Constructora. Determina el tick global en el que el gObj muere, la escena en la que se instancia la explosion y el daño que hace esta
    ExplosionBehaviour(int dmg, BattleScene* where, float lifeSpan) : lifeSpan(lifeSpan), currentLifeDuration(0), scene(where), damage(dmg), tr(nullptr), target(nullptr) {}
    static const int id = _EXPLOSION_BEHAVIOUR;
    //Checkea que haya pasado el tiempo establecido o que el game object haya impactado y elimina el gObj creando una explosion en caso positivo
    void update();
    void initComponent();
    CallBackCol explosionAttack();
};