#include "TentacleBehaviour.h"
#include "../../gameObjects/GameObject.h"
#include "../General Components/Transform.h"

// Constructor de TentacleBehaviour
TentacleBehaviour::TentacleBehaviour(bool mirror) {
	// Inicializar variables miembro
	initTime = 1;
	rotationTime = BOSS_CLOCK_ATTACKDURATION;
	delayTime = BOSS_CLOCK_DELAYTIME;
	elapsedTime = 0;
	maxWidth = 2 * BOSS_ENEMY_WIDTH;
	rotationCompleted = initCompleted = delayCompleted = false;
	isMirror = mirror;
}

// Inicializar el componente
void TentacleBehaviour::initComponent() {
	myTransform = gObj->getComponent<Transform>(); // Obtener referencia al componente Transform
	originalX = myTransform->getX(); // Guardar la posición X original
	originalY = myTransform->getY(); // Guardar la posición Y original
}

// Actualizar el componente
void TentacleBehaviour::update() {
	// Primer estado: Inicializar y extender el tentáculo
	if (elapsedTime < initTime && !initCompleted && !delayCompleted) {
		myTransform->setWidth(maxWidth / 10 * elapsedTime); // Aumentar el ancho del tentáculo
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
		if (elapsedTime >= initTime) {
			initCompleted = true; // Marcar la inicialización como completada
			elapsedTime = 0;
		}
	}
	// Segundo estado: Esperar un tiempo determinado
	else if (elapsedTime >= delayTime && initCompleted && !delayCompleted) {
		delayCompleted = true; // Marcar la espera como completada
		initCompleted = false;
		elapsedTime = 0;
	}
	// Tercer estado: Extender completamente el tentáculo
	else if (elapsedTime < initTime && delayCompleted && !initCompleted) {
		myTransform->setWidth(maxWidth / 10 + (maxWidth * 9) / 10 * elapsedTime); // Aumentar el ancho del tentáculo
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
		if (elapsedTime >= initTime) {
			initCompleted = true; // Marcar la extensión completa como completada
			elapsedTime = 0;
		}
	}
	// Cuarto estado: Rotar el tentáculo
	else if (elapsedTime < rotationTime && !rotationCompleted && delayCompleted && initCompleted) {
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); // Incrementar el tiempo transcurrido
		float angle = 180 * (SDLApplication::instance()->getDeltaTimeSeconds() / rotationTime); // Calcular el ángulo de rotación
		myTransform->rotate(angle); // Rotar el tentáculo
		if (elapsedTime >= rotationTime) {
			rotationCompleted = true; // Marcar la rotación como completada
			elapsedTime = 0;
			gObj->setAlive(false); // Marcar el objeto como inactivo
		}
	}
	// Incrementar el tiempo transcurrido durante la espera
	if (elapsedTime < delayTime && initCompleted && !delayCompleted) elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
}
