#pragma once
#include "Component.h"
class LifeTimeComponent :
    public Component
{
private:
    
    Uint32 deathTime;
public:
    LifeTimeComponent(Uint32 lifespan);
    static const int id = _LIFETIME;
    void update();
};