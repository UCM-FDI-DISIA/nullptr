#pragma once
#include "Component.h"
class LifeTimeComponent :
    public Component
{
private:
    //Duracion del gObj
    float lifeSpan;
    float currentLifeDuration = 0;
public:
    //Constructora. Determina el tick global en el que el gObj muere
    LifeTimeComponent(float lifeSpan);
    static const int id = _LIFETIME;
    //Checkea que haya pasado el tiempo establecido, y elimina el gObj en caso positivo
    void update();
};