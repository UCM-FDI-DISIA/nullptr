#include "HandUI.h"

void HandUI::initGameObject(SDLApplication* _g, CardComponent* _cComp) {
	// Obtener la mano del jugador
	game = _g;
	cardComp = _cComp;
	handPlayer = _cComp->getHand();

	// Crear las imagenes que se verán por pantalla
	int i = 1;
	for (int j = 0; j < MAX_HAND_SIZE; j++) {
		// Crear objeto
		GameObject* card = new GameObject();

		// Añadir transform, haciendo que la primera carta esté más alta que el resto; y la textura
		if (i == 1) card->addComponent<Transform>(Vector2D(X_CARD_POS - CARD_WIDTH / 2, Y_CARD_POS - 30), Vector2D(), CARD_WIDTH * 2, CARD_HEIGTH * 2, -15 + 10 * (i - 3));
		else card->addComponent<Transform>(Vector2D(X_CARD_POS * i - CARD_WIDTH / 2, Y_CARD_POS), Vector2D(), CARD_WIDTH * 2, CARD_HEIGTH * 2, -15 + 10 * (i - 3));
		card->addComponent<Image>(game->getTexture(PISTOLA));
		// card->addComponent<Image>(handPlayer[j]->getTexture());

		// Añadir a la deque de la UI y marcar iteración
		handUI.push_back(card);
		i++;
	}

	// Marcar como activa la primera carta
	active = handUI.begin();
}

// Renderizamos los GameObjects del deque
void HandUI::render() const {
	for (int i = 0; i < handUI.size(); i++) {
		handUI[i]->render();
	}
}

// Cambia la carta seleccionada, deseleccionando la anterior
void HandUI::changeSelected(bool key, int number) {
	// Deseleccionar la carta anterior, volviendo a su posición original
	(*active)->getComponent<Transform>()->setY(Y_CARD_POS);

	if (key) {
		if (number >= 0 && number < handUI.size()) {
			active = handUI.begin();
			std::advance(active, number);
		}
	}
	else {
		if (number == 1) ++active;
		else --active;
	}

	(*active)->getComponent<Transform>()->setY(Y_CARD_POS - 30);
}

void HandUI::discard(deque<Card*>::iterator discarded) {

}