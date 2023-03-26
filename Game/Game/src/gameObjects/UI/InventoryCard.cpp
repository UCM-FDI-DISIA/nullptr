#include "InventoryCard.h"
#include "../../scenes/InventoryScene.h"
#include "../../sdlutils/InputHandler.h"

void InventoryCard::initGameObject(InventoryScene* s, InventoryInfo* cd, int posL, int posD) {
	scene = s;
	cardData = cd;
	posLib = posL; posDeck = posD;

	addComponent<Transform>(LIBRARY_POSITIONS[posL], VECTOR_ZERO, CARD_WIDTH * 2, CARD_HEIGHT * 2);
	addComponent<Image>(cd->card->texture);

	// Creamos el marco, la imagen de la carta en el deck y su circulo si se debe
	if (posD != -1) {
		createOnDeckObjects(posL, posD);
	}
	else {
		frame = nullptr;
		deckCard = nullptr;
		deckNumber = nullptr;
		circle = nullptr;
	}

	// Creamos el objeto de rectangulo
	GameObject* rect = scene->addGameObject(_grp_UI);
	rect->addComponent<Transform>(LIBRARY_POSITIONS[posL] + CARD_RECTANGLE_OFFSET * 2, VECTOR_ZERO,
		CARD_RECTANGLE_WIDTH * 2, CARD_RECTANGLE_HEIGHT * 2);
	rect->addComponent<Image>(&sdlutils().images().at(CARD_RECTANGLE));

	// Creamos el texto de las cartas
	text = scene->addGameObject(_grp_UI);
	tr = text->addComponent<Transform>(LIBRARY_POSITIONS[posL] + CARD_RECTANGLE_OFFSET * 2, VECTOR_ZERO,
		CARD_RECTANGLE_WIDTH * 2, CARD_RECTANGLE_HEIGHT * 2);
	string content = " " + to_string(cardData->cuantityDeck) + "/" + to_string(cardData->cuantity) + " ";
	t = text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"), content, true);

}

void InventoryCard::createOnDeckObjects(int _pl, int _pd) {
	frame = scene->addGameObject();
	frame->addComponent<Transform>(LIBRARY_POSITIONS[_pl] - CARD_FRAME_OFFSET * 2, VECTOR_ZERO, CARD_FRAME_WIDTH * 2, CARD_FRAME_HEIGHT * 2);
	frame->addComponent<Image>(&sdlutils().images().at(CARD_FRAME));

	deckCard = scene->addGameObject();
	deckCard->addComponent<Transform>(DECK_POSITIONS[_pd], VECTOR_ZERO, CARD_WIDTH * 2, CARD_HEIGHT * 2);
	deckCard->addComponent<Image>(cardData->card->texture);

	circle = scene->addGameObject();
	circle->addComponent<Transform>(DECK_POSITIONS[_pd] + CARD_CIRCLE_OFFSET * 2, VECTOR_ZERO,
		CARD_CIRCLE_RADIOUS * 2, CARD_CIRCLE_RADIOUS * 2);
	circle->addComponent<Image>(&sdlutils().images().at(CARD_CIRCLE));

	deckNumber = scene->addGameObject();
	deckNumber->addComponent<Transform>(Vector2D(DECK_POSITIONS[_pd] + CARD_CIRCLE_OFFSET * 2 + Vector2D(5, CARD_CIRCLE_RADIOUS / 3)), VECTOR_ZERO, 
														CARD_CIRCLE_RADIOUS * 1.5f, CARD_CIRCLE_RADIOUS * 2);
	dN = deckNumber->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"), to_string(cardData->cuantityDeck), true);
}

void InventoryCard::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Cambia el estado según la posición del ratón
	if (isOver(mouseX, mouseY)) {
		st = OVER;
	}
	else {
		st = OUT;
	}
}

bool InventoryCard::isOver(int mx, int my) {
	return (mx >= tr->getPos().getX() && mx < tr->getPos().getX() + tr->getWidth()) &&
		(my >= tr->getPos().getY() && my < tr->getPos().getY() + tr->getHeight());
}

void InventoryCard::handleInput() {
	if (st == OVER && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT)) {
		OnDeckNumberChanges();
	}
}

void InventoryCard::OnDeckNumberChanges() {
	// SI PASO DE 0 A 1, HAY Q AÑADIR MARCO EN LA LIBRERIA, LA IMAGEN AL MAZO Y SU CIRCULO
	if (cardData->cuantityDeck == 0) {
		//Aumento el numero de cartas en mazo y cojo su posicion en el mazo
		cardData->cuantityDeck++;
		posDeck = scene->getFirstDeckPos();
		// Creo de nuevo los objetos
		createOnDeckObjects(posLib, posDeck);
		// ACTUALIZAR AMBOS TEXTOS
		t->changeText(" " + to_string(cardData->cuantityDeck) + "/" + to_string(cardData->cuantity) + " ");
		dN->changeText(to_string(cardData->cuantityDeck));
	}
	
	// SI PASO DEL MAXIMO DE CARTAS A 0 HAY Q ELIMINAR LA IMAGEN DE CARTA DEL MAZO
	else if (cardData->cuantityDeck == cardData->cuantity) {
		// Elimino los objetos
		frame->setAlive(false);
		frame = nullptr;

		deckCard->setAlive(false);
		deckCard = nullptr;

		scene->removeFromDeck(posLib);
		posDeck = -1;

		circle->setAlive(false);
		circle = nullptr;

		deckNumber->setAlive(false);
		deckNumber = nullptr;
		dN = nullptr;

		//Actualizo el numero y el texto
		cardData->cuantityDeck = 0;
		t->changeText(" " + to_string(cardData->cuantityDeck) + "/" + to_string(cardData->cuantity) + " ");
	}

	// SI SIMPLEMENTE AUMENTO, ACTUALIZAMOS EL TEXTO
	else {
		// Aumento el numero
		cardData->cuantityDeck++;
		// ACTUALIZAR AMBOS TEXTOS
		t->changeText(" " + to_string(cardData->cuantityDeck) + "/" + to_string(cardData->cuantity) + " ");
		dN->changeText(to_string(cardData->cuantityDeck));
	}
}