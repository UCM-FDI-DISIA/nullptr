#include "CardCounter.h"

void CardCounter::initGameObject(SDLApplication* _game, bool _ref, CardComponent* _data) {
	// Asigno los valores para saber si cuento el mazo, guardarme la referencia de las cartas del jugador y el numero lo seteo a 0
	amIDeck = _ref;
	myData = _data;
	currentNumber = 0;

	// Me guardo el Transform del objeto principal (para ajustar los numeros de acorde)
	Transform* trP;
	// Si soy el contador de cartas del mazo me coloco a la izquierda
	if (_ref) trP = addComponent<Transform>(Vector2D(LEFT_OFFSET, DOWN_OFFSET), Vector2D(0, 0), REVERSE_WIDTH, REVERSE_HEIGHT);
	// Si soy el contador de cartas de los descartes me coloco a la derecha
	else trP = addComponent<Transform>(Vector2D(WIN_WIDTH - RIGHT_OFFSET, DOWN_OFFSET), Vector2D(0, 0), REVERSE_WIDTH, REVERSE_HEIGHT);

	//Me guardo una referencia al componente de renderizado para anclarlo a la camara (asi tiene una posicion fija en pantalla)
	Image* im = addComponent<Image>(_game->getTexture("Reverse"));
	im->attachToCamera();

	//Creamos el objeto de las decenas: con sus componentes y sus animaciones
	decs = new GameObject();
	decs->addComponent<Transform>(Vector2D(trP->getPos().getX() + CARD_OFFSET_W, DOWN_OFFSET + CARD_OFFSET_H), Vector2D(0, 0), NUM_RENDER_W, NUM_RENDER_H);
	Animator* decAnim = decs->addComponent<Animator>(_game->getTexture("Numbers"),NUMBERS_WIDTH, NUMBERS_HEIGHT, NUMBERS_SPRITE_ROWS, NUMBERS_SPRITE_COLUMS);
	decAnim->attachToCamera();
	createAnims(decAnim);
	decAnim->play(to_string(0));

	//Creamos el objeto de las unidades: con sus componentes y sus animaciones
	unids = new GameObject();
	unids->addComponent<Transform>(Vector2D(trP->getPos().getX() + REVERSE_WIDTH/2 + CARD_OFFSET_W, DOWN_OFFSET + CARD_OFFSET_H), Vector2D(0, 0), NUM_RENDER_W, NUM_RENDER_H);
	Animator* uniAnim =  unids->addComponent<Animator>(_game->getTexture("Numbers"), NUMBERS_WIDTH, NUMBERS_HEIGHT, NUMBERS_SPRITE_ROWS, NUMBERS_SPRITE_COLUMS);
	uniAnim->attachToCamera();
	createAnims(uniAnim);
	uniAnim->play(to_string(0));
}

void CardCounter::update() {
	//Si cuento las cartas del mazo
	if (amIDeck) {
		//Si el numero ha cambiado...
		if (currentNumber != myData->getDeckSize()) {
			//Actualizo mi numero y calculo las decenas y las unidades
			currentNumber = myData->getDeckSize();
			int uni = currentNumber % 10;
			int dec = currentNumber / 10;

			//Creo una referencia del tipo Animator
			Animator* anim;
			//Cojo el Animator del objeto de las unidades y reproduzco la nueva animacion correspondiente
			anim = unids->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(uni));
			//COjo el Animator del objeto de las decenas y reproduzco la nueva animacion correspondiente
			anim = decs->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(dec));
		}
	}
	//Si cuento las cartas de la pila de descartes
	else {
		//Si el numero ha cambiado...
		if (currentNumber != myData->getPileSize()) {
			//Actualizo mi numero y calculo las decenas y las unidades
			currentNumber = myData->getPileSize();
			int uni = currentNumber % 10;
			int dec = currentNumber / 10;

			//Creo una referencia del tipo Animator
			Animator* anim;
			//Cojo el Animator del objeto de las unidades y reproduzco la nueva animacion correspondiente
			anim = unids->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(uni));
			//COjo el Animator del objeto de las decenas y reproduzco la nueva animacion correspondiente
			anim = decs->getComponent<Animator>();
			anim->stop();
			anim->play(to_string(dec));
		}
	}
}

//Para renderizar llamamos a los componentes del objeto padre y a los de los hijos
void CardCounter::render() const {
	GameObject::render();

	//Creamos una referencia para los animadores de los objetos hijos (y llamamos a los metodos para renderizar)
	Animator* anim = decs->getComponent<Animator>();
	anim->render();
	anim = unids->getComponent<Animator>();
	anim->render();
}

//Creamos una animacion por dígito posible (0-9)
void CardCounter::createAnims(Animator* &_anim) {
	for (int i = 0; i < 10; i++) {
		_anim->createAnim(std::to_string(i), i, i, 2, -1);
	}
}