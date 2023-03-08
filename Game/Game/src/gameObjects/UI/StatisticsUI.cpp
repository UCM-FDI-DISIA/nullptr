#include "../UI/StatisticsUI.h"

void StatisticsUI::initGameObject(int life, int mana) {
	// Barra superior
	statistics = new GameObject();
	statistics->addComponent<Transform>(UI_STATISTICS_POSITION, Vector2D(), UI_STATISTICS_WIDTH, UI_STATISTICS_HEIGHT);
	statistics->addComponent<Image>(SDLApplication::getTexture(STATISTICS));
	statistics->getComponent<Image>()->attachToCamera();

	// Medidor de éter
	etherMeterFrame = new GameObject();
	etherMeterFrame->addComponent<Transform>(UI_ETHER_FRAME_POSITION, Vector2D(), UI_ETHER_FRAME_WIDTH, UI_ETHER_FRAME_HEIGHT);
	etherMeterFrame->addComponent<Image>(SDLApplication::getTexture(ETHER_METER_FRAME));
	etherMeterFrame->getComponent<Image>()->attachToCamera();

	// Crear barras de vida
	createLifeBar(life);
	createManaBar(mana);
	createEtherMeter();

	// Inicialización de vida
	fullLife = life;
	fullMana = mana;

	// Crear los numeros de vida
	for (int i = 0; i < N_LIFE_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();
		
		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + 60 + (12 * i), 46), Vector2D(), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, 0);
		createNumberAnims(number, fullLife, i);

		// Añadir a su vector
		lifeCounter.push_back(number);
	}

	// Crear los numeros de maná
	for (int i = 0; i < N_MANA_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();

		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 140 + (12 * i), 46), Vector2D(), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, 0);
		createNumberAnims(number, fullMana, i);

		// Añadir a su vector
		manaCounter.push_back(number);
	}

	for (int i = 0; i < N_ETHER_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();
		cout << i;
		// Añadir componentes y crea animaciones
		if (i != 3) number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 35 + (20 * i), 15), Vector2D(), ST_NUMBERS_WIDTH * 1.8, ST_NUMBERS_HEIGHT * 1.8, 0);
		else number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 35 + (20 * i), 26), Vector2D(), ST_NUMBERS_WIDTH * 1.2, ST_NUMBERS_HEIGHT * 1.2, 0);
		createNumberAnims(number, 0, i, false);

		etherCounter.push_back(number);
	}
}

// Crea la barra de vida
void StatisticsUI::createLifeBar(int value) {
	// Añadir el objeto
	healthBar = new GameObject();

	// Componentes transform y animator
	healthBar->addComponent<Transform>(LIFEBAR_POSITION, Vector2D(), UI_BAR_WIDTH, UI_BAR_HEIGHT);
	auto anim = healthBar->addComponent<Animator>(SDLApplication::getTexture(LIFEBAR), BAR_WIDTH, BAR_HEIGHT, BAR_ROWS, BAR_COLUMNS);
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(LIFEBAR, BAR_START, BAR_END, BAR_FRAMERATE, -1);
	anim->play(LIFEBAR);

	// Componente de barra
	healthBar->addComponent<BarComponent>(true, value);
}

// Crea la barra de mana
void StatisticsUI::createManaBar(int value) {
	// Añadir el objeto
	manaBar = new GameObject();

	// Componentes transform y animator
	manaBar->addComponent<Transform>(MANABAR_POSITION, Vector2D(), UI_BAR_WIDTH, UI_BAR_HEIGHT);
	auto anim = manaBar->addComponent<Animator>(SDLApplication::getTexture(MANABAR), BAR_WIDTH, BAR_HEIGHT, BAR_ROWS, BAR_COLUMNS);
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(MANABAR, BAR_START, BAR_END, BAR_FRAMERATE, -1);
	anim->play(MANABAR);

	// Componente de barra
	manaBar->addComponent<BarComponent>(false, value);
}

// Crea el medidor de eter
void StatisticsUI::createEtherMeter() {
	// Añadir el objeto
	etherMeter = new GameObject();

	// Componentes transform y animator
	etherMeter->addComponent<Transform>(UI_ETHER_POSITION, Vector2D(), UI_ETHER_WIDTH, UI_ETHER_HEIGHT);
	auto anim = etherMeter->addComponent<Animator>(SDLApplication::getTexture("etherMeter"), ETHER_WIDTH, ETHER_HEIGHT, ETHER_ROWS, ETHER_COLUMNS);
	changeAnimatorSrcRelativeHeight(etherMeter, MAX_ETHER, 0);

	// Crear animaciones
	anim->attachToCamera();
	anim->createAnim("ether", ETHER_START, ETHER_END, ETHER_FRAMERATE, -1);
	anim->play("ether");
}

// Llama al update de los distintos GameObjects
void StatisticsUI::update() {
	healthBar->update();
	manaBar->update();
	etherMeter->update();
}

// Renderizar los distintos GameObjects
void StatisticsUI::render() const {
	statistics->render();
	healthBar->render();
	manaBar->render();
	etherMeterFrame->render();
	etherMeter->render();
	etherMeter->render();
	for (int i = 0; i < N_LIFE_COUNTER; i++) lifeCounter[i]->render();
	for (int i = 0; i < N_MANA_COUNTER; i++) manaCounter[i]->render();
	for (int i = 0; i < N_ETHER_COUNTER; i++) etherCounter[i]->render();
}

// Al cambiar la vida, actualizar componentes
void StatisticsUI::OnHealthChanges(float value) {
	changeAnimatorSrcRelativeWidth(healthBar, fullLife, value);
	changeNumbers(lifeCounter, value);
}

// Al cambiar el maná, actualizar componentes
void StatisticsUI::OnManaChanges(float value) {
	// Cambiar el tamaño de la animación respecto al maná gastado
	changeAnimatorSrcRelativeWidth(manaBar, fullMana, value);

	manaBar->getComponent<BarComponent>()->changeBar(value);
	changeNumbers(manaCounter, value);
}

void StatisticsUI::OnEtherChanges(float value) {
	// Cambiar el tamaño de la animación respecto al maná gastado
	changeAnimatorSrcRelativeHeight(etherMeter, 100, value);

	changeNumbers(etherCounter, value);
}

// Crear los números de la interfaz
void StatisticsUI::createNumberAnims(GameObject* obj, int value, int i, bool isBar) {
	// Obtener unidades del valor entrante
	tuple<cents, decs, unids> units = getUnits(value);

	// Añadir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture("statisticsNumbers"), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, ST_NUMBERS_ROWS, ST_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
	if (isBar) {
		// Reproducir "animacion" con el número correpondiente
		if (i == 0 || i == 4) anim->play(to_string(get<0>(units)));
		else if (i == 1 || i == 5) anim->play(to_string(get<1>(units)));
		else if (i == 2 || i == 6) anim->play(to_string(get<2>(units)));
		else if (i == 3) anim->play(to_string(10));
	}
	else {
		if (i == 0) anim->play(to_string(get<0>(units)));
		else if (i == 1) anim->play(to_string(get<1>(units)));
		else if (i == 2) anim->play(to_string(get<2>(units)));
		else if (i == 3) anim->play(to_string(11));
	}
}

// Cambia el valor de los números activan su animación correspondiente
void StatisticsUI::changeNumbers(vector<GameObject*> vect, int value) {
	// Obtener unidades
	tuple<cents, decs, unids> units = getUnits(value);
	
	// 0 centenas - 1 decenas - 2 unidades
	vect[0]->getComponent<Animator>()->play(to_string(get<0>(units)));
	vect[1]->getComponent<Animator>()->play(to_string(get<1>(units)));
	vect[2]->getComponent<Animator>()->play(to_string(get<2>(units)));
}

// Devuelve una tupla con el valor de las centenas, las decenas y las unidades
tuple<cents, decs, unids> StatisticsUI::getUnits(int value) {
	int cents = value / 100;
	int decs = (value - cents * 100) / 10;
	int unids = (value - cents * 100 - decs * 10);

	return make_tuple(cents, decs, unids);
}

// Cálcula y cambia el ancho de animación al correspondiente
void StatisticsUI::changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value) {
	float newSrcRectFactor = (100 * value) / (maxValue * 100);
	bar->getComponent<Animator>()->setSrcRectRelativeWidth(newSrcRectFactor);
}

// Cálcula y cambia el alto de animación al correspondiente
void StatisticsUI::changeAnimatorSrcRelativeHeight(GameObject* meter, float maxValue, float value) {
	float newSrcRectFactor = (100 * value) / (maxValue * 100);
	meter->getComponent<Animator>()->setSrcRectRelativeHeight(newSrcRectFactor);
}