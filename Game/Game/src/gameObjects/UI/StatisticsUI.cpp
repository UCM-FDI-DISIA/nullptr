#include "../UI/StatisticsUI.h"

void StatisticsUI::initGameObject(int life, int mana) {
	// Barra superior
	statistics = new GameObject();
	statistics->addComponent<Transform>(UI_STATISTICS_POSITION, Vector2D(), UI_STATISTICS_WIDTH * 2.5, UI_STATISTICS_HEIGHT * 2.5);
	statistics->addComponent<Image>(SDLApplication::getTexture(UI_STATISTICS));
	statistics->getComponent<Image>()->attachToCamera();

	// Medidor de éter
	etherMeter = new GameObject();
	etherMeter->addComponent<Transform>(UI_ETHER_POSITION, Vector2D(), UI_ETHER_WIDTH * 2.5 + 1, UI_ETHER_HEIGHT * 2.5);
	etherMeter->addComponent<Image>(SDLApplication::getTexture(UI_ETHER_METER));
	etherMeter->getComponent<Image>()->attachToCamera();

	// Crear barras de vida
	createLifeBar(life);
	createManaBar(mana);

	// Inicialización de vida
	fullLife = life;
	fullMana = mana;

	// Crear los numeros de vida
	for (int i = 0; i < 7; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();
		
		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + 60 + (12 * i), 46), Vector2D(), 9, 18, 0);
		createNumberAnims(number, fullLife, i);

		// Añadir a su vector
		lifeCounter.push_back(number);
	}

	// Crear los numeros de maná
	for (int i = 0; i < 7; i++) {
		// Crear el objeto
		GameObject* number = new GameObject();

		// Añadir componentes y crea animaciones
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 140 + (12 * i), 46), Vector2D(), 9, 18, 0);
		createNumberAnims(number, fullMana, i);

		// Añadir a su vector
		manaCounter.push_back(number);
	}
}

// Crea la barra de vida
void StatisticsUI::createLifeBar(int value) {
	// Añadir el objeto
	healthBar = new GameObject();

	// Componentes transform y animator
	healthBar->addComponent<Transform>(LIFEBAR_POSITION, Vector2D(), BAR_WIDTH * 2.5, BAR_HEIGHT * 2.5);
	auto anim = healthBar->addComponent<Animator>(SDLApplication::getTexture(LIFEBAR), BAR_WIDTH, BAR_HEIGHT, 4, 3);
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(LIFEBAR, 0, 10, 5, -1);
	anim->play(LIFEBAR);

	// Componente de barra
	healthBar->addComponent<BarComponent>(true, value);
}

// Crea la barra de mana
void StatisticsUI::createManaBar(int value) {
	// Añadir el objeto
	manaBar = new GameObject();

	// Componentes transform y animator
	manaBar->addComponent<Transform>(MANABAR_POSITION, Vector2D(), BAR_WIDTH * 2.5, BAR_HEIGHT * 2.5);
	auto anim = manaBar->addComponent<Animator>(SDLApplication::getTexture(MANABAR), BAR_WIDTH, BAR_HEIGHT, 4, 3);
	
	// Mantener en la cámara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(MANABAR, 0, 10, 5, -1);
	anim->play(MANABAR);

	// Componente de barra
	manaBar->addComponent<BarComponent>(false, value);
}

// Llama al update de los distintos GameObjects
void StatisticsUI::update() {
	statistics->update();
	healthBar->update();
	manaBar->update();
	etherMeter->update();
}

// Renderizar los distintos GameObjects
void StatisticsUI::render() const {
	statistics->render();
	healthBar->render();
	manaBar->render();
	etherMeter->render();
	for (int i = 0; i < 7; i++) lifeCounter[i]->render();
	for (int i = 0; i < 7; i++) manaCounter[i]->render();
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

// Crear los números de la interfaz
void StatisticsUI::createNumberAnims(GameObject* obj, int value, int i) {
	// Obtener unidades del valor entrante
	tuple<cents, decs, unids> units = getUnits(value);

	// Añadir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture("statisticsNumbers"), 9, 18, 6, 2);
	for (int j = 0; j < 11; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
	// Reproducir "animacion" con el número correpondien
	if (i == 0 || i == 4) anim->play(to_string(get<0>(units)));
	else if (i == 1 || i == 5) anim->play(to_string(get<1>(units)));
	else if (i == 2 || i == 6) anim->play(to_string(get<2>(units)));
	else if (i == 3) anim->play(to_string(10));
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