#include "../UI/StatisticsUI.h"

void StatisticsUI::initGameObject(int life, int mana) {
	// Barra superior
	statistics = new GameObject();
	statistics->addComponent<Transform>(UI_STATISTICS_POSITION, Vector2D(), UI_STATISTICS_WIDTH, UI_STATISTICS_HEIGHT);
	statistics->addComponent<Image>(SDLApplication::getTexture(STATISTICS))->attachToCamera();
	objs.push_back(statistics);

	// Medidor de éter
	etherMeterFrame = new GameObject();
	etherMeterFrame->addComponent<Transform>(UI_ETHER_FRAME_POSITION, Vector2D(), UI_ETHER_FRAME_WIDTH, UI_ETHER_FRAME_HEIGHT);
	etherMeterFrame->addComponent<Image>(SDLApplication::getTexture(ETHER_METER_FRAME))->attachToCamera();
	objs.push_back(etherMeterFrame);

	// Crear barras de vida
	createLifeBar(life);
	createManaBar(mana);
	createEtherMeter();

	// Inicialización de vida
	fullLife = life;
	fullMana = mana;
	actualEther = 0;

	// Crear los numeros de vida
	for (int i = 0; i < N_LIFE_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();
		
		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(Constant::getInt("WIN_WIDTH") / 2 + 60 + (12 * i), 46), Vector2D(), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, 0);
		createNumberAnims(number, fullLife, i);

		// Añadir a los vectores
		lifeCounter.push_back(number);
		objs.push_back(number);
	}

	// Crear los numeros de maná
	for (int i = 0; i < N_MANA_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();

		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 140 + (12 * i), 46), Vector2D(), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, 0);
		createNumberAnims(number, fullMana, i);

		// Añadir a su vector
		manaCounter.push_back(number);
		objs.push_back(number);
	}

	// Crear los números de éter
	for (int i = 0; i < N_ETHER_COUNTER; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();

		// Añadir componentes y crea animaciones
		if (i != 3) number->addComponent<Transform>(Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 35 + (20 * i), 15), Vector2D(), ST_NUMBERS_WIDTH * 1.8, ST_NUMBERS_HEIGHT * 1.8, 0);
		else number->addComponent<Transform>(Vector2D(Constant::getInt("WIN_WIDTH") / 2 - 35 + (20 * i), 26), Vector2D(), ST_NUMBERS_WIDTH * 1.2, ST_NUMBERS_HEIGHT * 1.2, 0);
		createNumberAnims(number, 0, i, false);

		etherCounter.push_back(number);
		objs.push_back(number);
	}
	// Componente de salida
	etherMeter->addComponent<ChargedPortalComponent>(etherCounter);
}

StatisticsUI::~StatisticsUI() {
	for (auto& gobj : objs) {
		delete gobj;
		gobj = nullptr;
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
	healthBar->addComponent<BarComponent>(value);

	// Añadir al vector
	objs.push_back(healthBar);
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
	anim->flipHorizontal();
	anim->createAnim(MANABAR, BAR_START, BAR_END, BAR_FRAMERATE, -1);
	anim->play(MANABAR);

	// Componente de barra
	manaBar->addComponent<BarComponent>(value);

	// Añadir al vector
	objs.push_back(manaBar);
}

// Crea el medidor de eter
void StatisticsUI::createEtherMeter() {
	// Añadir el objeto
	etherMeter = new GameObject();

	// Componentes transform y animator
	etherMeter->addComponent<Transform>(UI_ETHER_POSITION, Vector2D(), UI_ETHER_WIDTH, UI_ETHER_HEIGHT);
	auto anim = etherMeter->addComponent<Animator>(SDLApplication::getTexture(ETHER_METER), ETHER_WIDTH, ETHER_HEIGHT, ETHER_ROWS, ETHER_COLUMNS);

	// Crear animaciones
	anim->attachToCamera();
	anim->createAnim(ETHER_ANIM, ETHER_START, ETHER_END, ETHER_FRAMERATE, -1);
	anim->play(ETHER_ANIM);

	// Componente de barra
	auto barComp = etherMeter->addComponent<BarComponent>();
	barComp->changeAnimatorSrcRelativeHeight(etherMeter, MAX_ETHER, 0);

	// Añadir al vector
	objs.push_back(etherMeter);
}

// Llama al update de los distintos GameObjects
void StatisticsUI::update() {
	for (GameObject* g : objs) 
		if (g->isAlive()) g->update();
}

// Renderizar los distintos GameObjects
void StatisticsUI::render() const {
	for (GameObject* g : objs) 
		if (g->isAlive()) g->render();
}

// Al cambiar la vida, actualizar componentes
void StatisticsUI::onHealthChanges(float value) {
	healthBar->getComponent<BarComponent>()->onHealthChanges(value, fullLife, lifeCounter);
}

// Al cambiar el maná, actualizar componentes
void StatisticsUI::onManaChanges(float value) {
	manaBar->getComponent<BarComponent>()->onManaChanges(value, fullMana, manaCounter);
}

// Al cambiar el éter, actualizar componentes
void StatisticsUI::onEtherChanges(float value) {
	// Sumar éter y trampear si excede el límite
	actualEther += value;
	if (actualEther >= ETHER_LIMIT) actualEther = ETHER_LIMIT;

	// Transmitir información a la barra
	etherMeter->getComponent<BarComponent>()->onEtherChanges(actualEther, etherCounter);

	// Activar la posibilidad de salir si se ha completado al 100% la barra
	if (actualEther >= 100) etherMeter->getComponent<ChargedPortalComponent>()->activateExit();
}

// Crear los números de la interfaz
void StatisticsUI::createNumberAnims(GameObject* obj, int value, int i, bool isBar) {
	// Obtener unidades del valor entrante
	tuple<cents, decs, unids> units = healthBar->getComponent<BarComponent>()->getUnits(value);

	// Añadir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture(STATISTICS_NUMBERS), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, ST_NUMBERS_ROWS, ST_NUMBERS_COLUMNS);
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