#include "CardNumberButton.h"

void CardNumberButton::initGameObject(Vector2D _pos, InventoryInfo* _c) {
	tr = addComponent<Transform>(_pos + CARD_RECTANGLE_OFFSET * 2, VECTOR_ZERO, CARD_RECTANGLE_WIDTH, CARD_RECTANGLE_HEIGHT);
	addComponent<Image>(&sdlutils().images().at(CARD_RECTANGLE));

	
}