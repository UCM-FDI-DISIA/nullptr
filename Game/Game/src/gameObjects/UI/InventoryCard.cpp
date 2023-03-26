#include "InventoryCard.h"
#include "../../scenes/InventoryScene.h"

void InventoryCard::initGameObject(InventoryScene* s, InventoryInfo* cd, int posL, int posD) {
	scene = s;
	cardData = cd;
	
	addComponent<Transform>(LIBRARY_POSITIONS[posL], VECTOR_ZERO, CARD_WIDTH * 2, CARD_HEIGHT * 2);
	addComponent<Image>(cd->card->texture);

	// Creamos el marco, la imagen de la carta en el deck y su circulo si se debe
	if (posD != -1) {
		frame = scene->addGameObject();
		frame->addComponent<Transform>(LIBRARY_POSITIONS[posL] - CARD_FRAME_OFFSET * 2, VECTOR_ZERO, CARD_FRAME_WIDTH * 2, CARD_FRAME_HEIGHT * 2);
		frame->addComponent<Image>(&sdlutils().images().at(CARD_FRAME));

		deckCard = scene->addGameObject();
		deckCard->addComponent<Transform>(DECK_POSITIONS[posD], VECTOR_ZERO, CARD_WIDTH * 2, CARD_HEIGHT * 2);
		deckCard->addComponent<Image>(cd->card->texture);

		GameObject* circle = scene->addGameObject();
		circle->addComponent<Transform>(DECK_POSITIONS[posD] + CARD_CIRCLE_OFFSET * 2, VECTOR_ZERO, 
												CARD_CIRCLE_RADIOUS * 2, CARD_CIRCLE_RADIOUS * 2);
		circle->addComponent<Image>(&sdlutils().images().at(CARD_CIRCLE));

		deckNumber = scene->addGameObject();
		deckNumber->addComponent<Transform>();
		deckNumber->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"), "3", true);
	}
	else {
		frame = nullptr;
		deckCard = nullptr;
		deckNumber = nullptr;
	}

	// Creamos el objeto de rectangulo
	GameObject* rect = scene->addGameObject(_grp_UI);
	rect->addComponent<Transform>(LIBRARY_POSITIONS[posL] + CARD_RECTANGLE_OFFSET * 2, VECTOR_ZERO,
		CARD_RECTANGLE_WIDTH * 2, CARD_RECTANGLE_HEIGHT * 2);
	rect->addComponent<Image>(&sdlutils().images().at(CARD_RECTANGLE));

	// Creamos el texto de las cartas
	text = scene->addGameObject(_grp_UI);
	text->addComponent<Transform>(LIBRARY_POSITIONS[posL] + CARD_RECTANGLE_OFFSET * 2, VECTOR_ZERO,
		CARD_RECTANGLE_WIDTH * 2, CARD_RECTANGLE_HEIGHT * 2);
	text->addComponent<TextComponent>(&sdlutils().fonts().at("ARIAL24"), "3 / 3", true);

}



void InventoryCard::OnDeckNumberChanges() {
	// SI PASO DE 0 A 1, HAY Q AÑADIR MARCO EN LA LIBRERIA, LA IMAGEN AL MAZO Y SU CIRCULO
	if (cardData->cuantityDeck == 0) {
		frame = scene->addGameObject();
		frame->addComponent<Transform>(getComponent<Transform>()->getPos() - CARD_FRAME_OFFSET * 2, VECTOR_ZERO,
			CARD_FRAME_WIDTH * 2, CARD_FRAME_HEIGHT * 2);
		frame->addComponent<Image>(&sdlutils().images().at(CARD_FRAME));
		cardData->cuantityDeck++;
	}
	
	// SI PASO DEL MAXIMO DE CARTAS A 0 HAY Q ELIMINAR LA IMAGEN DE CARTA DEL MAZO
	else if (cardData->cuantityDeck == cardData->cuantity) {
		frame->setAlive(false);
		frame = nullptr;

		deckCard->setAlive(false);
		deckCard = nullptr;

		deckNumber->setAlive(false);
		deckNumber = nullptr;

		// ACTUALIZAR EL TEXTO

		cardData->cuantityDeck = 0;
	}

	// SI SIMPLEMENTE AUMENTO, ACTUALIZAMOS EL TEXTO
	else {
		// ACTUALIZAR AMBOS TEXTOS
	}
}