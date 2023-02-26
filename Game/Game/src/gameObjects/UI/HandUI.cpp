#include "HandUI.h"

void HandUI::initGameObject(CardComponent* _cComp) {
	// Puntero al cardcomponent
	cardComp = _cComp;

	// Crear las cartas reflejadas por pantalla
	createUI();
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
	if (handUI.size() > 0) {
		changeSelected(true, 0);
		switch (handUI.size()) {
			case 1: rearrangeOne(); break;
			case 2: rearrangeTwo(); break;
			case 3: rearrangeThree(); break;
		}
	}
}

// Crear las cartas de la UI según la mano del jugador, iniciando variables y posicionándolas correctamente
void HandUI::createUI() {
	// Borrar la mano anterior y obtener la mano actual del jugador
	handUI.clear();
	handPlayer = cardComp->getHand();

	// Crear las 4 cartas con sus posiciones correspondientes
	createCard(0, X1_4CARDS_POS, Y_CARD_POS_SELECTED, -10);
	createCard(1, X2_4CARDS_POS, Y_CARD_POS, -5);
	createCard(2, X3_4CARDS_POS, Y_CARD_POS, 5);
	createCard(3, X4_4CARDS_POS, Y_CARD_POS, 10);

	// Marcar como activa la primera carta
	active = handUI.begin();
}

void HandUI::createCard(int i, int posX, int posY, int rotation) {
	// Crear objeto
	GameObject* card = new GameObject();

	// Añadir transform con los valores correspondientes y la textura
	card->addComponent<Transform>(Vector2D(posX, posY), Vector2D(), UI_CARD_WIDTH, UI_CARD_HEIGHT, rotation);
	card->addComponent<Image>(handPlayer[i]->getTexture());

	// Añadir a la deque de la UI
	handUI.push_back(card);
}

// Posiciona las 3 cartas restantes de forma que una esté en medio sin rotación, y las otras a su alrededor ligeramente rotadas
void HandUI::rearrangeThree() {
	// Iterador para recorrer la mano y puntero a transform para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;

	// Primera carta
	tr = (*it)->getComponent<Transform>();
	tr->setX(X1_3CARDS_POS); tr->setRotation(-5);
	it++;

	// Segunda carta
	tr = (*it)->getComponent<Transform>();
	tr->setX(CENTERED_CARD_POS); tr->setRotation(0);
	it++;

	// Tercera carta
	tr = (*it)->getComponent<Transform>();
	tr->setX(X3_3CARDS_POS); tr->setRotation(5);
}

// Posiciona las 2 cartas restantes correctamente, ligeramente rotadas
void HandUI::rearrangeTwo() {
	// Iterador para recorrer la mano y puntero a transform para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;

	// Primera carta
	tr = (*it)->getComponent<Transform>();
	tr->setX(X2_4CARDS_POS); tr->setRotation(-5);
	it++;

	// Segunda carta
	tr = (*it)->getComponent<Transform>();
	tr->setX(X3_4CARDS_POS); tr->setRotation(5);
}

// Posiciona la carta restante en el centro sin rotación
void HandUI::rearrangeOne() {
	(*active)->getComponent<Transform>()->setX(CENTERED_CARD_POS);
	(*active)->getComponent<Transform>()->setRotation(0);
}