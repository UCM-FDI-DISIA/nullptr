#include "CardCounter.h"

CardCounter::CardCounter(SDLApplication* _game, bool _ref, CardComponent* _data) {
	amIDeck = _ref;
	myData = _data;
	currentNumber = 0;

	Transform* trP;
	if (_ref) trP = addComponent<Transform>(Vector2D(REVERSE_WIDTH / 4, WIN_HEIGHT - (6 * REVERSE_HEIGHT / 5)), Vector2D(0, 0), REVERSE_WIDTH, REVERSE_HEIGHT);
	else trP = addComponent<Transform>(Vector2D(WIN_WIDTH - 5 * REVERSE_WIDTH / 4, WIN_HEIGHT - (6 * REVERSE_HEIGHT / 5)), Vector2D(0, 0), 
																											REVERSE_WIDTH, REVERSE_HEIGHT);
	addComponent<Image>(_game->getTexture("Reverse"));

	//Creamos el objeto de las decenas: con sus componentes y sus animaciones
	decenas = new GameObject();
	decenas->addComponent<Transform>(Vector2D(trP->getPos().getX() + 2, trP->getPos().getY() - 21), Vector2D(0, 0), NUMBERS_WIDTH / 5, NUMBERS_HEIGHT / 5);
	Animator* decAnim = decenas->addComponent<Animator>(_game->getTexture("Numbers"),
		NUMBERS_WIDTH, NUMBERS_HEIGHT, NUMBERS_SPRITE_ROWS, NUMBERS_SPRITE_COLUMS);
	createAnims(decAnim);


	unidades = new GameObject();
	unidades->addComponent<Transform>(Vector2D(trP->getPos().getX() + trP->getWidth() / 2 + 2, trP->getPos().getY() - 21), Vector2D(0, 0),
		NUMBERS_WIDTH / 5, NUMBERS_HEIGHT / 5);
	Animator* uniAnim =  unidades->addComponent<Animator>(_game->getTexture("Numbers"),
		NUMBERS_WIDTH, NUMBERS_HEIGHT, NUMBERS_SPRITE_ROWS, NUMBERS_SPRITE_COLUMS);
	createAnims(uniAnim);

}

void CardCounter::update() {
	if (amIDeck) {
		if (currentNumber != myData->getDeckSize()) {
			currentNumber = myData->getDeckSize();
			int uni = currentNumber % 10;
			int dec = currentNumber / 10;

			Animator* anim;

			anim = unidades->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(uni));

			anim = decenas->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(dec));
		}
	}

	else {
		if (currentNumber != myData->getPileSize()) currentNumber = myData->getDeckSize();
	}


}

void CardCounter::render() {
	getComponent<Image>()->render();
	decenas->getComponent<Animator>()->render();
	unidades->getComponent<Animator>()->render();
}

void CardCounter::createAnims(Animator* _anim) {
	for (int i = 0; i < 10; i++) {
		_anim->createAnim(std::to_string(i), i, i, 2, -1);
	}
}