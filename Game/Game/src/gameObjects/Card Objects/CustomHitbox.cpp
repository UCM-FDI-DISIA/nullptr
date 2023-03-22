#include "CustomHitbox.h"

// CustomHitbox::CustomHitbox(const HitboxData& data) : Hitbox(data) {} // Elimina esta línea

void CustomHitbox::initCustomHitbox(const HitboxData& data) {
    initGameObject(data);
}

void CustomHitbox::update() {
    Hitbox::update();
    if (updateFunction) {
        updateFunction(this);
    }
}

void CustomHitbox::setUpdateFunction(std::function<void(GameObject*)> function) {
    updateFunction = function;
}

