#include "TargetedComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../General Components/Transform.h"

// Constructor de TargetedComponent
TargetedComponent::TargetedComponent(Transform* player) {
	playerTransform = player;
	initTime = 1;
	delayTime = BOSS_TARGETED_DELAY;
	elapsedTime = 0;
	maxWidth = 3 * BOSS_ENEMY_WIDTH;
	initCompleted = delayCompleted = false;
	actualRot = 0;
}

// Inicializar el componente
void TargetedComponent::initComponent() {
	myTransform = gObj->getComponent<Transform>(); // Obtener referencia al componente Transform
	originalX = myTransform->getX(); // Guardar la posición X original
	originalY = myTransform->getY(); // Guardar la posición Y original
}

// Actualizar el componente
void TargetedComponent::update() {
    if (gObj->getComponent<Image>() == NULL)
    {
        // Primer estado: Inicializar y extender el objeto
        if (elapsedTime < initTime && !initCompleted && !delayCompleted) {
            myTransform->setWidth(maxWidth * 3 / 10 * elapsedTime); // Aumentar el ancho del objeto
            elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
            if (elapsedTime >= initTime) {
                initCompleted = true; // Marcar la inicialización como completada
                elapsedTime = 0;
            }
        }
        // Segundo estado: Seguir al jugador durante el tiempo de espera y almacenar su posición al final del tiempo de espera
        if (elapsedTime < delayTime && initCompleted && !delayCompleted) {
            elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
            myTransform->rotate(myTransform->getAngle(playerTransform->getPos(), myTransform->getPos()) - actualRot); // Rotar el objeto hacia el jugador
            actualRot = myTransform->getRotation(); // Actualizar la rotación actual
            if (elapsedTime >= delayTime) {
                lastPlayerTransform = playerTransform->getPos(); // Almacenar la posición del jugador al final del tiempo de espera
                delayCompleted = true;
                initCompleted = false;
                elapsedTime = 0;
            }
        }
        // Tercer estado: Extender completamente el objeto y mantenerlo apuntando hacia la última posición del jugador
        else if (elapsedTime < initTime && delayCompleted && !initCompleted) {
            myTransform->setWidth(maxWidth * 3 / 10 + (maxWidth * 7) / 10 * elapsedTime); // Aumentar el ancho del objeto
            elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
            if (elapsedTime >= initTime) {
                initCompleted = true; // Marcar la extensión completa como completada
                elapsedTime = 0;
            }
        }
        // Marcar el objeto como inactivo si se han completado todos los estados
        if (delayCompleted && initCompleted) gObj->setAlive(false);
    }
    else {
        // Seguir al jugador mientras no haya llegado el momento de expandirse
        if (elapsedTime < delayTime) {
            elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
            myTransform->rotate(myTransform->getAngle(playerTransform->getPos(), myTransform->getPos()) - actualRot); // Rotar el objeto hacia el jugador
            actualRot = myTransform->getRotation(); // Actualizar la rotación actual

            // Fijar el ancho del objeto al tamaño máximo
            myTransform->setWidth(maxWidth);
        }
        // Se mantiene estatico
        else {

        }
        // Marcar el objeto como inactivo si se han completado todos los estados
        if (delayCompleted && initCompleted) gObj->setAlive(false);
    }
}
