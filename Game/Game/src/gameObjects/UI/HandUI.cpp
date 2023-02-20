#include "HandUI.h"

void HandUI::initGameObject(CardComponent* _cComp) {
	cardComp = _cComp;

	// Crear las cartas reflejadas por pantalla
	createUI();
	// NOTA: La propia clase CardComponent llama a la creación de la UI
}

// Renderizar los GameObjects del deque (de lo contrario solo se renderiza un objeto vacío)
void HandUI::render() const {
	for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) handUI[i]->render();
	}
}

// Cambia la carta seleccionada, deseleccionando la anterior
void HandUI::changeSelected(bool key, int number) {
	// Deseleccionar la carta anterior, volviendo a su posición original si no es esta llamada debida a un descarte
	if (active != handUI.end()) (*active)->getComponent<Transform>()->setY(Y_CARD_POS);

	// Si se ha cambiado pulsando teclas
	if (key) {
		// Avanzar el iterador que apunta a la carta activa hasta la correspondiente
		active = handUI.begin();
		std::advance(active, number);
	}
	// ... si ha sido por la rueda del ratón
	else {
		// Scroll hacia arriba
		if (number == 1) ++active;
		// ... scroll hacia abajo
		else --active;
	}

	// Seleccionar la carta escogida
	(*active)->getComponent<Transform>()->setY(Y_CARD_POS_SELECTED);
}

// Borrar la carta correspondiente
void HandUI::discard(deque<Card*>::iterator discarded) {
	// Busqueda de la carta correspondiente. Aux: iterador que referencia al mazo de la UI, para saber cual borrar
	int i = 0;
	auto aux = handUI.begin();
	handPlayer = cardComp->getHand();
	bool discard = false;
	while (i < handPlayer.size() && !discard) {
		// Si la carta es la buscada, en aux ya debe de estar la carta de la UI, se sale del bucle
		if (handPlayer[i] == *discarded) discard = true;
		// ... de lo contrario, continuar iterando comprobando si es la siguiente carta de la UI
		else { i++; aux++; }
	}

	// Borrar carta y asignar la nueva activa
	active = handUI.erase(aux);

	// Si la mano no se ha vaciado, marcar la carta inicial
	if (handUI.size() > 0) changeSelected(true, 0);
}

// Crear las cartas de la UI según la mano del jugador, iniciando variables y posicionándolas correctamente
void HandUI::createUI() {
	// Borrar la mano anterior y obtener la mano actual del jugador
	handUI.clear();
	handPlayer = cardComp->getHand();

	// Crear las imagenes que se verán por pantalla
	int i = 1;
	for (int j = 0; j < MAX_HAND_SIZE; j++) {
		// Crear objeto
		GameObject* card = new GameObject();

		// Añadir transform, haciendo que la primera carta esté más alta que el resto; y la textura
		if (i == 1) card->addComponent<Transform>(Vector2D(X_CARD_POS - CARD_WIDTH / 2, Y_CARD_POS_SELECTED), Vector2D(), CARD_WIDTH * 4, CARD_HEIGTH * 4, 0);
		else card->addComponent<Transform>(Vector2D(X_CARD_POS * i - CARD_WIDTH / 2, Y_CARD_POS), Vector2D(), CARD_WIDTH * 4, CARD_HEIGTH * 4, 0);
		card->addComponent<Image>(handPlayer[j]->getTexture());

		// Añadir a la deque de la UI y marcar iteración
		handUI.push_back(card);
		i++;
	}

	// Marcar como activa la primera carta
	active = handUI.begin();
}