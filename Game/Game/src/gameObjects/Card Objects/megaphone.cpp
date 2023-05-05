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
    Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
    

    

    for (int i = 0; i < numProjectiles; i++) {
        // Calcular el factor de interpolación entre -1 y 1
        float t = -1.0f + 2.0f * (float)i / (float)(numProjectiles - 1);

        // Interpolar entre 'perp' y '-perp' usando el factor t
        Vector2D currentOffset = perp * t * spacingBetweenProjectiles * (numProjectiles - i);

        // Sumar la posición del jugador, la dirección y el desplazamiento actual
        Vector2D startPos = playerPos + dir * 20.0f * (i + 1) + currentOffset;
        
        
        Hitbox::HitboxData data = { startPos, VECTOR_ZERO, spriteRotation, 30 + 40 * i, 30 + 90 * i, "null", _grp_ENEMIES };

        GameObject* hitbox = where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 0.5, data);

        if(i == numProjectiles - 1){
            auto anim = hitbox-> addComponent<Animator>(SDLApplication::getTexture("MegaphoneAtt"), 29, 32, 2, 6);
            anim->createAnim("Attack", Animation(0, 11, 18, 1));
            anim->play("Attack");
        }
    }

}

//Se cura 
void  MegaphoneCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
    Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
    where->getPlayer()->getComponent<HealthComponent>()->heal(6 * remainingUses);
    remainingUses = 0;
}