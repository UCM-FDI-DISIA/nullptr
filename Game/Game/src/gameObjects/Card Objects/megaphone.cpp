#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//se crea un cono de sonido que mata a los enemigos
void MegaphoneCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    int numProjectiles = 4;
    float spacingBetweenProjectiles = 10.0f; // Distancia en p�xeles entre cada proyectil

    Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();

    // Calcular el vector perpendicular a 'dir'
    Vector2D perp(-dir.getY(), dir.getX());

    // Calcular el �ngulo de rotaci�n del sprite
    float spriteRotation = atan2(dir.getY(), dir.getX()) * 180.0f / M_PI;

    for (int i = 0; i < numProjectiles; i++) {
        // Calcular el factor de interpolaci�n entre -1 y 1
        float t = -1.0f + 2.0f * (float)i / (float)(numProjectiles - 1);

        // Interpolar entre 'perp' y '-perp' usando el factor t
        Vector2D currentOffset = perp * t * spacingBetweenProjectiles * (numProjectiles - i);

        // Sumar la posici�n del jugador, la direcci�n y el desplazamiento actual
        Vector2D startPos = playerPos + dir * 20.0f * (i + 1) + currentOffset;

        Hitbox::HitboxData data = { startPos, Vector2D(), spriteRotation, 50 * i, 100 * i, Constant::getString("SOWND_ATTACK"), _grp_ENEMIES};

        where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 0.5, data);
    }
}

//Se disparan todas las balas
void  MegaphoneCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    Hitbox::HitboxData data = { playerPos, Vector2D(), 0, 3, 3, Constant::getString("HEAL_AREA"), _grp_PLAYER};

    where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 6* remainingUses, 0.5, data, 0.1);

    remainingUses = 0;

}