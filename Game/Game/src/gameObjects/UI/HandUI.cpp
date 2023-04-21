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

// Renderizar los GameObjects del deque (de lo contrario solo se renderiza un objeto vacío)
void HandUI::render() const {
	for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) {
			auto object = handUI[i];
			object->card->render();
			object->ammoNumber.first->render();
			object->ammoNumber.second->render();
			object->manaNumber.first->render();
			object->manaNumber.second->render();
			/*for (int i = 0; i < object->ammo; i++) {
				object->ammoBlocks[i]->render();
				SDL_Rect rect = object->ammoBlocks[i]->getComponent<Transform>()->getRect();
				SDL_RenderDrawRect(sdlutils().renderer(), &rect);
			}
			SDL_Rect rect = object->card->getComponent<Transform>()->getRect();
			SDL_RenderDrawRect(sdlutils().renderer(), &rect);*/
		}
	}
}

// Reposicona una carta, haciendo que esté o no seleccionada dependiendo de los datos recibidos
void HandUI::repositionSelected(int cardPos, int offset) {
	// Reposicionar carta
	(*active)->card->getComponent<Transform>()->setY(cardPos);

	// Coger transforms de los componentes
	auto trAmmoDecs = (*active)->ammoNumber.first->getComponent<Transform>();
	auto trAmmoUnits = (*active)->ammoNumber.second->getComponent<Transform>();
	auto trManaDecs = (*active)->manaNumber.first->getComponent<Transform>();
	auto trManaUnits = (*active)->manaNumber.second->getComponent<Transform>();

	// Reposicionarlos
	trAmmoDecs->setY(trAmmoDecs->getY() + offset);
	trAmmoUnits->setY(trAmmoUnits->getY() + offset);
	trManaDecs->setY(trManaDecs->getY() + offset);
	trManaUnits->setY(trManaUnits->getY() + offset);
	/*for (int i = 0; i < (*active)->ammo; i++) {
		auto tr = (*active)->ammoBlocks[i]->getComponent<Transform>();
		tr->setY(tr->getY() + SELECTED_OFFSET);
	}*/
}

// Cambia la carta seleccionada, deseleccionando la anterior
void HandUI::changeSelected(bool key, int number) {
	// Deseleccionar la carta anterior, volviendo a su posición original si no es esta llamada debida a un descarte
	if (active != handUI.end())
		repositionSelected(Constant::getInt("Y_CARD_POS"), Constant::getInt("SELECTED_OFFSET"));

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
	repositionSelected(Constant::getInt("Y_CARD_POS_SELECTED"), -Constant::getInt("SELECTED_OFFSET"));
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
}

// Crear las cartas de la UI según la mano del jugador, iniciando variables y posicionándolas correctamente
void HandUI::createUI() {
	// Borrar la mano anterior y obtener la mano actual del jugador
	handUI.clear();
	handPlayer = cardComp->getHand();

	// Crear las 4 cartas con sus posiciones correspondientes
	createCard(0, Constant::getInt("X1_4CARDS_POS"), Constant::getInt("Y_CARD_POS_SELECTED"), -10);
	createCard(1, Constant::getInt("X2_4CARDS_POS"), Constant::getInt("Y_CARD_POS"), -5);
	createCard(2, Constant::getInt("X3_4CARDS_POS"), Constant::getInt("Y_CARD_POS"), 5);
	createCard(3, Constant::getInt("X4_4CARDS_POS"), Constant::getInt("Y_CARD_POS"), 10);

	// Marcar como activa la primera carta
	active = handUI.begin();
}

void HandUI::createCard(int i, int posX, int posY, int rotation) {
	// Crear estructura
	UICard* newCard = new UICard(); 

	// Crear la carta y añadirle sus componentes image y tansform
	newCard->card = new GameObject();
	newCard->card->addComponent<Transform>(Vector2D(posX, posY), Vector2D(), Constant::getInt("UI_CARD_WIDTH"), Constant::getInt("UI_CARD_HEIGHT"), rotation);
	newCard->card->addComponent<Image>(handPlayer[i]->getTexture());

	// Guardar munición y obtener maná
	newCard->maxAmmo = handPlayer[i]->getUses();
	newCard->ammo = handPlayer[i]->getUses();
	int mana = handPlayer[i]->getMana();

	// Variables de posición de números y barra de munición
	Vector2D posDecsAmmo; Vector2D posUnitsAmmo;
	Vector2D posDecsMana; Vector2D posUnitsMana;
	switch (i) {
		case 0:
			posDecsAmmo = Vector2D(posX + Constant::getInt("X1_AMMO_XOFFSET_DECS"), posY + Constant::getInt("X1_AMMO_YOFFSET_DECS"));
			posUnitsAmmo = Vector2D(posX + Constant::getInt("X1_AMMO_XOFFSET_UNITS"), posY + Constant::getInt("X1_AMMO_YOFFSET_UNITS"));
			posDecsMana = Vector2D(posX + Constant::getInt("X1_MANA_XOFFSET_DECS"), posY + Constant::getInt("X1_MANA_YOFFSET_DECS"));
			posUnitsMana = Vector2D(posX + Constant::getInt("X1_MANA_XOFFSET_UNITS"), posY + Constant::getInt("X1_MANA_YOFFSET_UNITS"));
			break;
		case 1:
			posDecsAmmo = Vector2D(posX + Constant::getInt("X2_AMMO_XOFFSET_DECS"), posY + Constant::getInt("X2_AMMO_YOFFSET_DECS"));
			posUnitsAmmo = Vector2D(posX + Constant::getInt("X2_AMMO_XOFFSET_UNITS"), posY + Constant::getInt("X2_AMMO_YOFFSET_UNITS"));
			posDecsMana = Vector2D(posX + Constant::getInt("X2_MANA_XOFFSET_DECS"), posY + Constant::getInt("X2_MANA_YOFFSET_DECS"));
			posUnitsMana = Vector2D(posX + Constant::getInt("X2_MANA_XOFFSET_UNITS"), posY + Constant::getInt("X2_MANA_YOFFSET_UNITS"));
			break;
		case 2:
			posDecsAmmo = Vector2D(posX + Constant::getInt("X3_AMMO_XOFFSET_DECS"), posY + Constant::getInt("X3_AMMO_YOFFSET_DECS"));
			posUnitsAmmo = Vector2D(posX + Constant::getInt("X3_AMMO_XOFFSET_UNITS"), posY + Constant::getInt("X3_AMMO_YOFFSET_UNITS"));
			posDecsMana = Vector2D(posX + Constant::getInt("X3_MANA_XOFFSET_DECS"), posY + Constant::getInt("X3_MANA_YOFFSET_DECS"));
			posUnitsMana = Vector2D(posX + Constant::getInt("X3_MANA_XOFFSET_UNITS"), posY + Constant::getInt("X3_MANA_YOFFSET_UNITS"));
			break;
		case 3:
			posDecsAmmo = Vector2D(posX + Constant::getInt("X4_AMMO_XOFFSET_DECS"), posY + Constant::getInt("X4_AMMO_YOFFSET_DECS"));
			posUnitsAmmo = Vector2D(posX + Constant::getInt("X4_AMMO_XOFFSET_UNITS"), posY + Constant::getInt("X4_AMMO_YOFFSET_UNITS"));
			posDecsMana = Vector2D(posX + Constant::getInt("X4_MANA_XOFFSET_DECS"), posY + Constant::getInt("X4_MANA_YOFFSET_DECS"));
			posUnitsMana = Vector2D(posX + Constant::getInt("X4_MANA_XOFFSET_UNITS"), posY + Constant::getInt("X4_MANA_YOFFSET_UNITS"));
			break;
	}

	// Crear números
	newCard->ammoNumber.first = createNumber(posDecsAmmo, rotation, newCard->maxAmmo / 10, 'a');
	newCard->ammoNumber.second = createNumber(posUnitsAmmo, rotation, newCard->maxAmmo % 10, 'a');
	newCard->manaNumber.first = createNumber(posDecsMana, rotation, mana / 10, 'm');
	newCard->manaNumber.second = createNumber(posUnitsMana, rotation, mana % 10, 'm');

	/* // Crear bloques de munición
	int width = (40 * 3) / (newCard->maxAmmo / 1.0f);
	for (int i = 0; i < newCard->maxAmmo; i++) {
		auto block = new GameObject();

		int posX0 = posX + 14 * 3 + width * i;
		int posY0 = posY + 6 * 3;
		float rotRad = rotation * M_PI * 180.0f;
		int newPosX = posX0 * cos(rotRad) - posY0 * sin(rotRad);
		int newPosY = posX0 * sin(rotRad) + posY0 * cos(rotRad);
		
		block->addComponent<Transform>(Vector2D(newPosX, newPosY), Vector2D(), width, 5 * 3, rotation);
		block->addComponent<Image>(SDLApplication::getTexture(CARD_AMMO));
		
		newCard->ammoBlocks.push_back(block);
	}*/

	// Añadir a la deque de la UI
	handUI.push_back(newCard);
}

// Crear un número según los datos recibidos
GameObject* HandUI::createNumber(Vector2D pos, float rotation, int value, char type) {
	// Crear objeto
	auto number = new GameObject();

	// Añadir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), Constant::getInt("UI_AMMO_NUMBERS_WIDTH"), Constant::getInt("UI_AMMO_NUMBERS_HEIGHT"), rotation);
	createNumberAnims(number, value, type);

	// Devolver el número creado
	return number;
}

// Reposiciona una carta y a todos sus componentes a partir de datos recibidos
void HandUI::rearrangeCard(deque<UICard*>::iterator it, int cardPos, int rotation,
	tuple<int, int, int, float> ammoPos, tuple<int, int, int, int> manaPos) {
	// Puntero a transforms para posicionar
	Transform* tr = (*it)->card->getComponent<Transform>();;
	Transform* trAmmoDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	Transform* trAmmoUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	Transform* trManaDecs = (*it)->manaNumber.first->getComponent<Transform>();
	Transform* trManaUnits = (*it)->manaNumber.second->getComponent<Transform>();

	// Cambiar los transforms anteriores con las variables recibidas
	tr->setX(cardPos); tr->setRotation(rotation);
	trAmmoDecs->setPos(Vector2D(tr->getX() + get<0>(ammoPos), tr->getY() + get<1>(ammoPos))); trAmmoDecs->setRotation(rotation);
	trAmmoUnits->setPos(Vector2D(tr->getX() + get<2>(ammoPos), tr->getY() + get<3>(ammoPos))); trAmmoUnits->setRotation(rotation);
	trManaDecs->setPos(Vector2D(tr->getX() + get<0>(manaPos), tr->getY() + get<1>(manaPos))); trManaDecs->setRotation(rotation);
	trManaUnits->setPos(Vector2D(tr->getX() + get<2>(manaPos), tr->getY() + get<3>(manaPos))); trManaUnits->setRotation(rotation);
}

// Posiciona las 3 cartas restantes de forma que una esté en medio sin rotación, y las otras a su alrededor ligeramente rotadas
void HandUI::rearrangeThree() {
	// Iterador para recorrer la mano
	auto it = handUI.begin();

	// Primera carta
	rearrangeCard(it, Constant::getInt("X1_3CARDS_POS"), -5,
		make_tuple(Constant::getInt("X2_AMMO_XOFFSET_DECS"), Constant::getInt("X2_AMMO_YOFFSET_DECS"), Constant::getInt("X2_AMMO_XOFFSET_UNITS"), Constant::getInt("X2_AMMO_YOFFSET_UNITS")),
		make_tuple(Constant::getInt("X2_MANA_XOFFSET_DECS"), Constant::getInt("X2_MANA_YOFFSET_DECS"), Constant::getInt("X2_MANA_XOFFSET_UNITS"), Constant::getInt("X2_MANA_YOFFSET_UNITS")));
	it++;

	// Segunda carta
	rearrangeCard(it, Constant::getInt("CENTERED_CARD_POS"), 0,
		make_tuple(Constant::getInt("XC_AMMO_XOFFSET_DECS"), Constant::getInt("XC_AMMO_YOFFSET"), Constant::getInt("XC_AMMO_XOFFSET_UNITS"), Constant::getInt("XC_AMMO_YOFFSET")),
		make_tuple(Constant::getInt("XC_MANA_XOFFSET_DECS"), Constant::getInt("XC_MANA_YOFFSET"), Constant::getInt("XC_MANA_XOFFSET_UNITS"), Constant::getInt("XC_MANA_YOFFSET")));
	it++;

	// Tercera carta
	rearrangeCard(it, Constant::getInt("X3_3CARDS_POS"), 5,
		make_tuple(Constant::getInt("X3_AMMO_XOFFSET_DECS"), Constant::getInt("X3_AMMO_YOFFSET_DECS"), Constant::getInt("X3_AMMO_XOFFSET_UNITS"), Constant::getInt("X3_AMMO_YOFFSET_UNITS")),
		make_tuple(Constant::getInt("X3_MANA_XOFFSET_DECS"), Constant::getInt("X3_MANA_YOFFSET_DECS"), Constant::getInt("X3_MANA_XOFFSET_UNITS"), Constant::getInt("X3_MANA_YOFFSET_UNITS")));
	it++;
}

// Posiciona las 2 cartas restantes correctamente, ligeramente rotadas
void HandUI::rearrangeTwo() {
	// Iterador para recorrer la mano
	auto it = handUI.begin();

	// Primera carta
	rearrangeCard(it, Constant::getInt("X2_4CARDS_POS"), -5,
		make_tuple(Constant::getInt("X2_AMMO_XOFFSET_DECS"), Constant::getInt("X2_AMMO_YOFFSET_DECS"), Constant::getInt("X2_AMMO_XOFFSET_UNITS"), Constant::getInt("X2_AMMO_YOFFSET_UNITS")),
		make_tuple(Constant::getInt("X2_MANA_XOFFSET_DECS"), Constant::getInt("X2_MANA_YOFFSET_DECS"), Constant::getInt("X2_MANA_XOFFSET_UNITS"), Constant::getInt("X2_MANA_YOFFSET_UNITS")));
	it++;

	// Segunda carta
	rearrangeCard(it, Constant::getInt("X3_4CARDS_POS"), 5,
		make_tuple(Constant::getInt("X3_AMMO_XOFFSET_DECS"), Constant::getInt("X3_AMMO_YOFFSET_DECS"), Constant::getInt("X3_AMMO_XOFFSET_UNITS"), Constant::getInt("X3_AMMO_YOFFSET_UNITS")),
		make_tuple(Constant::getInt("X3_MANA_XOFFSET_DECS"), Constant::getInt("X3_MANA_YOFFSET_DECS"), Constant::getInt("X3_MANA_XOFFSET_UNITS"), Constant::getInt("X3_MANA_YOFFSET_UNITS")));
}

// Posiciona la carta restante en el centro sin rotación
void HandUI::rearrangeOne() {
	// Iterador para recorrer la mano
	auto it = active;

	// Primera carta
	rearrangeCard(it, Constant::getInt("CENTERED_CARD_POS"), 0,
		make_tuple(Constant::getInt("XC_AMMO_XOFFSET_DECS"), Constant::getInt("XC_AMMO_YOFFSET"), Constant::getInt("XC_AMMO_XOFFSET_UNITS"), Constant::getInt("XC_AMMO_YOFFSET")),
		make_tuple(Constant::getInt("XC_MANA_XOFFSET_DECS"), Constant::getInt("XC_MANA_YOFFSET"), Constant::getInt("XC_MANA_XOFFSET_UNITS"), Constant::getInt("XC_MANA_YOFFSET")));
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
void HandUI::createNumberAnims(GameObject* obj, int value, char type) {
	// Seleccionar textura
	Texture* txt;
	if (type == 'a') txt = SDLApplication::getTexture(Constant::getString("STATISTICS_NUMBERS"));
	else txt = SDLApplication::getTexture(Constant::getString("CARDS_NUMBERS"));

	// Añadir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(txt, Constant::getInt("CARDS_NUMBERS_WIDTH"), Constant::getInt("CARDS_NUMBERS_HEIGHT"), Constant::getInt("CARDS_NUMBERS_ROWS"), Constant::getInt("CARDS_NUMBERS_COLUMNS"));
	for (int j = 0; j < Constant::getInt("N_NUMBERS") - 2; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
	// Reproducir animación correspondiente
	anim->play(to_string(value));
}