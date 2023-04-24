#include "CardCounter.h"

void CardCounter::initGameObject(bool _ref, CardComponent* _data) {
	// Asigno los valores para saber si cuento el mazo, guardarme la referencia de las cartas del jugador y el numero lo seteo a 0
	amIDeck = _ref;
	myData = _data;
	currentNumber = 0;

	// Me guardo el Transform del objeto principal (para ajustar los numeros de acorde)
	Transform* trP;
	// Si soy el contador de cartas del mazo me coloco a la izquierda
	int right = Constant::getInt("WIN_WIDTH") - 2 * Constant::getInt("REVERSE_WIDTH");
	if (_ref) trP = addComponent<Transform>(Vector2D(Constant::getFloat("LEFT_OFFSET"), Constant::getFloat("DOWN_OFFSET")), Vector2D(), Constant::getInt("BS_REVERSE_WIDTH"), Constant::getInt("BS_REVERSE_HEIGHT"));
	// Si soy el contador de cartas de los descartes me coloco a la derecha
	else trP = addComponent<Transform>(Vector2D(right, Constant::getFloat("DOWN_OFFSET")), Vector2D(), Constant::getInt("BS_REVERSE_WIDTH"), Constant::getInt("BS_REVERSE_HEIGHT"));

	if (_ref)
	{
		//SI soy mazo debo ense�ar la animacion de barajear
		Animator* anim = addComponent<Animator>(SDLApplication::getTexture(Constant::getString("SHUFFLING_CARDS")), 58, 93, 1, 5);
		anim->attachToCamera();
		anim->createAnim(Constant::getString("SHUFFLING_CARDS"), 0, 4, 5, 1);
		anim->createAnim(IDLE, 0, 0, 1, 1);
		anim->play(IDLE);
	}
	else
	{
		//Si no soy mazo simplemente renderizo el reverso de la carta
		Image* im = addComponent<Image>(SDLApplication::getTexture(Constant::getTextureName("REVERSE")));
		im->attachToCamera();
	}

	//Creamos el objeto de las decenas: con sus componentes y sus animaciones
	decs = new GameObject();
	decs->addComponent<Transform>(Vector2D(trP->getPos().getX() + Constant::getFloat("CARD_OFFSET_W"), Constant::getFloat("DOWN_OFFSET") + Constant::getFloat("CARD_OFFSET_H")), Vector2D(), Constant::getFloat("NUM_RENDER_W")), Constant::getFloat("NUM_RENDER_H");
	Animator* decAnim = decs->addComponent<Animator>(SDLApplication::getTexture(Constant::getTextureName("NUMBERS")), Constant::getInt("NUMBERS_WIDTH"), Constant::getInt("NUMBERS_HEIGHT"), Constant::getInt("NUMBERS_SPRITE_ROWS"), Constant::getInt("NUMBERS_SPRITE_COLUMS"));
	decAnim->attachToCamera();
	createAnims(decAnim);
	decAnim->play(to_string(0));

	//Creamos el objeto de las unidades: con sus componentes y sus animaciones
	unids = new GameObject();
	unids->addComponent<Transform>(Vector2D(trP->getPos().getX() + Constant::getFloat("REVERSE_WIDTH") / 2 + Constant::getFloat("CARD_OFFSET_W") + 5, Constant::getFloat("DOWN_OFFSET") + Constant::getFloat("CARD_OFFSET_H")), Vector2D(), Constant::getFloat("NUM_RENDER_W"), Constant::getFloat("NUM_RENDER_H"));
	Animator* uniAnim =  unids->addComponent<Animator>(SDLApplication::getTexture(Constant::getTextureName("NUMBERS")), Constant::getInt("NUMBERS_WIDTH"), Constant::getInt("NUMBERS_HEIGHT"), Constant::getInt("NUMBERS_SPRITE_ROWS"), Constant::getInt("NUMBERS_SPRITE_COLUMS"));
	uniAnim->attachToCamera();
	createAnims(uniAnim);
	uniAnim->play(to_string(0));
}

void CardCounter::update() {

	//Si soy mazo debo actualizar mis componentes para que se vea la animacion
	if (amIDeck) GameObject::update();

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
			int uni = myData->getPileSize() % 10;
			int dec = myData->getPileSize() / 10;

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

			//Actualizo mi numero y calculo las decenas y las unidades
			currentNumber = myData->getPileSize();
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

//Creamos una animacion por d�gito posible (0-9)
void CardCounter::createAnims(Animator* &_anim) {
	for (int i = 0; i < 10; i++) {
		_anim->createAnim(std::to_string(i), i, i, 2, -1);
	}
}

//Metodo para reproducir la animacion de barajar el mazo
void CardCounter::showShuffle() {
	if (amIDeck) { getComponent<Animator>()->play(Constant::getString("SHUFFLING_CARDS")); }
}