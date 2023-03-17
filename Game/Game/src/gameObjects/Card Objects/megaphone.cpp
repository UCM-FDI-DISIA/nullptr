#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//se crea un cono de sonido que mata a los enemigos
void MegaphoneCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    int numProjectiles = 4;
    float spacingBetweenProjectiles = 10.0f; // Distancia en píxeles entre cada proyectil

    Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();

    // Calcular el vector perpendicular a 'dir'
    Vector2D perp(-dir.getY(), dir.getX());

    // Calcular el ángulo de rotación del sprite
    float spriteRotation = atan2(dir.getY(), dir.getX()) * 180.0f / M_PI;

    for (int i = 0; i < numProjectiles; i++) {
        // Calcular el factor de interpolación entre -1 y 1
        float t = -1.0f + 2.0f * (float)i / (float)(numProjectiles - 1);

        // Interpolar entre 'perp' y '-perp' usando el factor t
        Vector2D currentOffset = perp * t * spacingBetweenProjectiles * (numProjectiles - i);

        // Sumar la posición del jugador, la dirección y el desplazamiento actual
        Vector2D startPos = playerPos + dir * 20.0f * (i + 1) + currentOffset;

        Hitbox::HitboxData data = { startPos, VECTOR_ZERO, spriteRotation, 50 * i, 100 * i, "Sound", _grp_ENEMIES };

        where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
    }
}



//Se disparan todas las balas
void  MegaphoneCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED, 0, 16, 16, "Bullet", _grp_ENEMIES };
	float size = 250;
	string sprite = "Bullet";

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 50 * (remainingUses / 8), false, 2, StatusComponent::NONE, size, size, sprite, where, data);


	remainingUses = 0;

}