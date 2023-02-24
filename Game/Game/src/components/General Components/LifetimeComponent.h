#pragma once
#include "../Component.h"
class LifeTimeComponent :
    public Component
{
private:
    //Duracion del gObj
    Uint32 deathTime;
public:
    //Constructora. Determina el tick global en el que el gObj muere
    LifeTimeComponent(Uint32 lifespan);
    static const int id = _LIFETIME;
    //Checkea que haya pasado el tiempo establecido, y elimina el gObj en caso positivo
    void update();
};