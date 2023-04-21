#include "../UI/StatisticsUI.h"

void StatisticsUI::initGameObject(int life, int mana) {
	// Barra superior
	statistics = new GameObject();
	statistics->addComponent<Transform>(Constant::getVector2D("UI_STATISTICS_POSITION"), Vector2D(), Constant::getFloat("UI_STATISTICS_WIDTH"), Constant::getFloat("UI_STATISTICS_HEIGHT"));
	statistics->addComponent<Image>(SDLApplication::getTexture(Constant::getTextureName("STATISTICS")))->attachToCamera();
	objs.push_back(statistics);

	// Medidor de éter
	etherMeterFrame = new GameObject();
	etherMeterFrame->addComponent<Transform>(Constant::getVector2D("UI_ETHER_FRAME_POSITION"), Vector2D(), Constant::getFloat("UI_ETHER_FRAME_WIDTH"), Constant::getFloat("UI_ETHER_FRAME_HEIGHT"), 0);
	etherMeterFrame->addComponent<Image>(SDLApplication::getTexture(Constant::getTextureName("ETHER_METER_FRAME")))->attachToCamera();
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
	for (int i = 0; i < Constant::getInt("N_LIFE_COUNTER"); i++) {
		// Crear el objeto
		GameObject* number = new GameObject();
		
		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 + 60 + (12 * i), 46), Vector2D(), Constant::getInt("ST_NUMBERS_WIDTH"), Constant::getInt("ST_NUMBERS_HEIGHT"), 0);
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
		number->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 140 + (12 * i), 46), Vector2D(), Constant::getInt("ST_NUMBERS_WIDTH"), Constant::getInt("ST_NUMBERS_HEIGHT"), 0);
		createNumberAnims(number, (int)fullMana, i);

		// Añadir a su vector
		manaCounter.push_back(number);
		objs.push_back(number);
	}

	// Crear los números de éter
	for (int i = 0; i < Constant::getInt("N_ETHER_COUNTER"); i++) {
		// Crear el objeto
		GameObject* number = new GameObject();

		// Añadir componentes y crea animaciones
		if (i != 3) number->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 35 + (20 * i), 15), Vector2D(), Constant::getInt("ST_NUMBERS_WIDTH") * 1.8, Constant::getInt("ST_NUMBERS_HEIGHT") * 1.8, 0);
		else number->addComponent<Transform>(Vector2D(Constant::getFloat("WIN_WIDTH") / 2 - 35 + (20 * i), 26), Vector2D(), Constant::getInt("ST_NUMBERS_WIDTH") * 1.2, Constant::getInt("ST_NUMBERS_HEIGHT") * 1.2, 0);
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
	healthBar->addComponent<Transform>(Constant::getVector2D("LIFEBAR_POSITION"), Vector2D(), Constant::getInt("UI_BAR_WIDTH"), Constant::getInt("UI_BAR_HEIGHT"));
	auto anim = healthBar->addComponent<Animator>(SDLApplication::getTexture(Constant::getString("LIFEBAR")), Constant::getInt("BAR_WIDTH"), Constant::getInt("BAR_HEIGHT"), Constant::getInt("BAR_ROWS"), Constant::getInt("BAR_COLUMNS"));
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(Constant::getString("LIFEBAR"), Constant::getInt("BAR_START"), Constant::getInt("BAR_END"), Constant::getInt("BAR_FRAMERATE"), -1);
	anim->play(Constant::getString("LIFEBAR"));

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
	manaBar->addComponent<Transform>(Constant::getVector2D("MANABAR_POSITION"), Vector2D(), Constant::getInt("UI_BAR_WIDTH"), Constant::getInt("UI_BAR_HEIGHT"));
	auto anim = manaBar->addComponent<Animator>(SDLApplication::getTexture(Constant::getString("MANABAR")), Constant::getInt("BAR_WIDTH"), Constant::getInt("BAR_HEIGHT"), Constant::getInt("BAR_ROWS"), Constant::getInt("BAR_COLUMNS"));
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->flipHorizontal();
	anim->createAnim(Constant::getString("MANABAR"), Constant::getInt("BAR_START"), Constant::getInt("BAR_END"), Constant::getInt("BAR_FRAMERATE"), -1);
	anim->play(Constant::getString("MANABAR"));

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
	etherMeter->addComponent<Transform>(Constant::getVector2D("UI_ETHER_POSITION"), Vector2D(), Constant::getInt("UI_ETHER_WIDTH"), Constant::getInt("UI_ETHER_HEIGHT"));
	auto anim = etherMeter->addComponent<Animator>(SDLApplication::getTexture(Constant::getString("ETHER_METER")), Constant::getInt("ETHER_WIDTH"), Constant::getInt("ETHER_HEIGHT"), Constant::getInt("ETHER_ROWS"), Constant::getInt("ETHER_COLUMNS"));

	// Crear animaciones
	anim->attachToCamera();
	anim->createAnim(Constant::getString("ETHER_ANIM"), Constant::getInt("ETHER_START"), Constant::getInt("ETHER_END"), Constant::getInt("ETHER_FRAMERATE"), -1);
	anim->play(Constant::getString("ETHER_ANIM"));

	// Componente de barra
	auto barComp = etherMeter->addComponent<BarComponent>();
	barComp->changeAnimatorSrcRelativeHeight(etherMeter, Constant::getFloat("MAX_ETHER"), 0);

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
	if (actualEther >= Constant::getFloat("ETHER_LIMIT")) actualEther = Constant::getFloat("ETHER_LIMIT");

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
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture(Constant::getTextureName("STATISTICS_NUMBERS")), Constant::getInt("ST_NUMBERS_WIDTH"), Constant::getInt("ST_NUMBERS_HEIGHT"), Constant::getInt("ST_NUMBERS_ROWS"), Constant::getInt("ST_NUMBERS_COLUMNS"));
	for (int j = 0; j < Constant::getInt("N_NUMBERS"); j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
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