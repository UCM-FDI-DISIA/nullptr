#include "HandUI.h"

void HandUI::initGameObject(CardComponent* _cComp) {
	// Puntero al cardcomponent
	cardComp = _cComp;

	// Crear las cartas reflejadas por pantalla
	createUI();
}


HandUI::~HandUI() {
	for (auto gobj : handUI) delete gobj;
}

void HandUI::update() {
	/*for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) {
			auto object = handUI[i];
			object->ammoBar->update();
		}
	}*/
}

// Renderizar los GameObjects del deque (de lo contrario solo se renderiza un objeto vacío)
void HandUI::render() const {
	for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) {
			auto object = handUI[i];
			object->card->render();
			object->ammoNumber.first->render();
			object->ammoNumber.second->render();
			/*object->ammoBar->render();*/
			for (int i = 0; i < object->ammo; i++) {
				object->ammoBlocks[i]->render();
				/*SDL_Rect rect = object->ammoBlocks[i]->getComponent<Transform>()->getRect();
				SDL_RenderDrawRect(sdlutils().renderer(), &rect);*/
			}
			/*SDL_Rect rect = object->card->getComponent<Transform>()->getRect();
			SDL_RenderDrawRect(sdlutils().renderer(), &rect);*/
		}
	}
}

// Cambia la carta seleccionada, deseleccionando la anterior
void HandUI::changeSelected(bool key, int number) {
	// Deseleccionar la carta anterior, volviendo a su posición original si no es esta llamada debida a un descarte
	if (active != handUI.end()) {
		(*active)->card->getComponent<Transform>()->setY(Y_CARD_POS);
		auto trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
		auto trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
		// auto trBar = (*active)->ammoBar->getComponent<Transform>();
		trDecs->setY(trDecs->getY() + 60);
		trUnits->setY(trUnits->getY() + 60);
		for (int i = 0; i < (*active)->ammo; i++) {
			auto tr = (*active)->ammoBlocks[i]->getComponent<Transform>();
			tr->setY(tr->getY() + 60);
		}
 		// trBar->setY(trBar->getY() + 60);
	}

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
	(*active)->card->getComponent<Transform>()->setY(Y_CARD_POS_SELECTED);
	auto trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
	auto trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
	// auto trBar = (*active)->ammoBar->getComponent<Transform>();
	trDecs->setY(trDecs->getY() - 60);
	trUnits->setY(trUnits->getY() - 60);
	for (int i = 0; i < (*active)->ammo; i++) {
		auto tr = (*active)->ammoBlocks[i]->getComponent<Transform>();
		tr->setY(tr->getY() - 60);
	}
	// trBar->setY(trBar->getY() - 60);
}

// Borrar la carta correspondiente
void HandUI::discard(deque<Card*>::iterator discarded) {
	// Buscar y borrar carta y asignar la nueva activa
	auto aux = searchCard(discarded);
	delete *aux;
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

// Reduce la munición
void HandUI::changeAmmo(deque<Card*>::iterator used) {
	// Buscar y reducir su munición
	auto aux = searchCard(used);
	(*aux)->ammo--;

	// Mostrar número correcto
	(*aux)->ammoNumber.first->getComponent<Animator>()->play(to_string((*aux)->ammo / 10));
	(*aux)->ammoNumber.second->getComponent<Animator>()->play(to_string((*aux)->ammo - (*aux)->ammo / 10));

	// Reducir tamaño de la barra
	/*changeAnimatorSrcRelativeWidth((*aux)->ammoBar, (*aux)->maxAmmo, (*aux)->ammo);
	auto tr = (*aux)->ammoBar->getComponent<Transform>();
	tr->setY(tr->getY() + (tr->getWidth() * sin(tr->getRotation()) * M_PI / 180.0f) / 2);*/
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
	// Crear estructura
	UICard* newCard = new UICard(); 

	// Crear la carta y añadirle sus componentes image y tansform
	newCard->card = new GameObject();
	newCard->card->addComponent<Transform>(Vector2D(posX, posY), Vector2D(), UI_CARD_WIDTH, UI_CARD_HEIGHT, rotation);
	newCard->card->addComponent<Image>(handPlayer[i]->getTexture());

	// Guardar munición
	newCard->maxAmmo = handPlayer[i]->getUses();
	newCard->ammo = handPlayer[i]->getUses();

	// Variables de posición de números y barra de munición
	Vector2D posDecsAmmo; Vector2D posUnitsAmmo;
	Vector2D posDecsMana; Vector2D posUnitsMana;
	switch (i) {
		case 0:
			posDecsAmmo = Vector2D(posX + X1_XOFFSET_DECS, posY + X1_YOFFSET_DECS);
			posUnitsAmmo = Vector2D(posX + X1_XOFFSET_UNITS, posY + X1_YOFFSET_UNITS);
			// posBar = Vector2D(posX + 22, posY + 17.5);
			break;
		case 1:
			posDecsAmmo = Vector2D(posX + X2_XOFFSET_DECS, posY + X2_YOFFSET_DECS);
			posUnitsAmmo = Vector2D(posX + X2_XOFFSET_UNITS, posY + X2_YOFFSET_UNITS);
			// posBar = Vector2D(posX + 32, posY + 17.5);
			break;
		case 2:
			posDecsAmmo = Vector2D(posX + X3_XOFFSET_DECS, posY + X3_YOFFSET_DECS);
			posUnitsAmmo = Vector2D(posX + X3_XOFFSET_UNITS, posY + X3_YOFFSET_UNITS);
			// posBar = Vector2D(posX + 52, posY + 20);
			break;
		case 3:
			posDecsAmmo = Vector2D(posX + X4_XOFFSET_DECS, posY + X4_YOFFSET_DECS);
			posUnitsAmmo = Vector2D(posX + X4_XOFFSET_UNITS, posY + X4_YOFFSET_UNITS);
			// posBar = Vector2D(posX + 61, posY + 22);
			break;
	}

	// Crear números
	newCard->ammoNumber.first = createNumber(posDecsAmmo, rotation, newCard->maxAmmo / 10);
	newCard->ammoNumber.second = createNumber(posUnitsAmmo, rotation, newCard->maxAmmo - (newCard->maxAmmo / 10));

	int width = (40 * 3) / (newCard->maxAmmo / 1.0f);
	for (int i = 0; i < newCard->maxAmmo; i++) {
		auto block = new GameObject();

		int posX0 = posX + 14 * 3 + width * i;
		int posY0 = posY + 6 * 3;
		float rotRad = rotation * M_PI * 180.0f;
		int newPosX = posX0 * cos(rotRad) - posY0 * sin(rotRad);
		int newPosY = posX0 * sin(rotRad) + posY0 * cos(rotRad); // + ((sin(rotation) / width) * i)
		
		block->addComponent<Transform>(Vector2D(newPosX, newPosY), Vector2D(), width, 5 * 3, rotation);
		block->addComponent<Image>(SDLApplication::getTexture(CARD_AMMO));
		
		newCard->ammoBlocks.push_back(block);
	}

	// Crear barra de munición
	/*newCard->ammoBar = new GameObject();
	newCard->ammoBar->addComponent<Transform>(posBar, Vector2D(), 40 * 3, 5 * 3, rotation);
	auto anim = newCard->ammoBar->addComponent<Animator>(SDLApplication::getTexture(CARD_AMMO), 40, 5, 4, 1);*/

	// Mantener en la cámara y crear y reproducir animaciones
	/*anim->attachToCamera();
	anim->createAnim(CARD_AMMO, 0, 4, 6, -1);
	anim->play(CARD_AMMO);*/

	// Añadir a la deque de la UI
	handUI.push_back(newCard);
}

// Crear un número según los datos recibidos
GameObject* HandUI::createNumber(Vector2D pos, float rotation, int value) {
	// Crear objeto
	auto number = new GameObject();

	// Añadir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), UI_AMMO_NUMBERS_WIDTH, UI_AMMO_NUMBERS_HEIGHT, rotation);
	createNumberAnims(number, value);

	// Devolver el número creado
	return number;
}

// Posiciona las 3 cartas restantes de forma que una esté en medio sin rotación, y las otras a su alrededor ligeramente rotadas
void HandUI::rearrangeThree() {
	// Iterador para recorrer la mano y puntero a transforms para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	// Transform* trBar = nullptr;

	// Primera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X1_3CARDS_POS); tr->setRotation(-5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X2_XOFFSET_DECS, tr->getY() + X2_YOFFSET_DECS)); trDecs->setRotation(-5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X2_XOFFSET_UNITS, tr->getY() + X2_YOFFSET_UNITS)); trUnits->setRotation(-5);
	/*trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 32, tr->getY() + 17)); trBar->setRotation(-5);*/
	it++;

	// Segunda carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(CENTERED_CARD_POS); tr->setRotation(0);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + XC_XOFFSET_DECS, tr->getY() + XC_YOFFSET)); trDecs->setRotation(0);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + XC_XOFFSET_UNITS, tr->getY() + XC_YOFFSET)); trUnits->setRotation(0);
	/*trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 42, tr->getY() + 18)); trBar->setRotation(0);*/
	it++;

	// Tercera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X3_3CARDS_POS); tr->setRotation(5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X3_XOFFSET_DECS, tr->getY() + X3_YOFFSET_DECS)); trDecs->setRotation(5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X3_XOFFSET_UNITS, tr->getY() + X3_YOFFSET_UNITS)); trUnits->setRotation(5);
	/*trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 51.5, tr->getY() + 20)); trBar->setRotation(5);*/
}

// Posiciona las 2 cartas restantes correctamente, ligeramente rotadas
void HandUI::rearrangeTwo() {
	// Iterador para recorrer la mano y puntero a transform para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	// Transform* trBar = nullptr;

	// Primera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X2_4CARDS_POS); tr->setRotation(-5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X2_XOFFSET_DECS, tr->getY() + X2_YOFFSET_DECS)); trDecs->setRotation(-5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X2_XOFFSET_UNITS, tr->getY() + X2_YOFFSET_UNITS)); trUnits->setRotation(-5);
	/*trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 32, tr->getY() + 17)); trBar->setRotation(-5);*/
	it++;

	// Segunda carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X3_4CARDS_POS); tr->setRotation(5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X3_XOFFSET_DECS, tr->getY() + X3_YOFFSET_DECS)); trDecs->setRotation(5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X3_XOFFSET_UNITS, tr->getY() + X3_YOFFSET_UNITS)); trUnits->setRotation(5);
	/*trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 51.5, tr->getY() + 20)); trBar->setRotation(5);*/
}

// Posiciona la carta restante en el centro sin rotación
void HandUI::rearrangeOne() {
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	// Transform* trBar = nullptr;

	tr = (*active)->card->getComponent<Transform>();
	tr->setX(CENTERED_CARD_POS);
	tr->setRotation(0);
	trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + XC_XOFFSET_DECS, tr->getY() + XC_YOFFSET)); trDecs->setRotation(0);
	trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + XC_XOFFSET_UNITS, tr->getY() + XC_YOFFSET)); trUnits->setRotation(0);
	/*trBar = (*active)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 42, tr->getY() + 18)); trBar->setRotation(0);*/
}

// Buscar la carta correspondiente y devolver un iterador apuntando a esta
deque<UICard*>::iterator HandUI::searchCard(deque<Card*>::iterator searched) {
	// Busqueda de la carta correspondiente. Aux: iterador que referencia al mazo de la UI, para saber cual borrar
	int i = 0;
	auto aux = handUI.begin();
	handPlayer = cardComp->getHand();
	bool discard = false;
	while (i < handPlayer.size() && !discard) {
		// Si la carta es la buscada, en aux ya debe de estar la carta de la UI, se sale del bucle
		if (handPlayer[i] == *searched) discard = true;
		// ... de lo contrario, continuar iterando comprobando si es la siguiente carta de la UI
		else { i++; aux++; }
	}

	return aux;
}

// Crear los números de la interfaz
void HandUI::createNumberAnims(GameObject* obj, int value) {
	// Añadir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture(STATISTICS_NUMBERS), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, ST_NUMBERS_ROWS, ST_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
	// Reproducir animación correspondiente
	anim->play(to_string(value));
}