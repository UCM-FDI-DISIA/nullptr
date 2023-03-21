#pragma once
#include "Hitbox.h"

class CustomHitbox : public Hitbox {
public:
    // CustomHitbox(const HitboxData& data); // Elimina esta línea
    void initCustomHitbox(const HitboxData& data); // Añade esta línea

    virtual void update() override;
    void setUpdateFunction(std::function<void(GameObject*)> function);

private:
    std::function<void(GameObject*)> updateFunction;
};