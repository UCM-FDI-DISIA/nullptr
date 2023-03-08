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

	int cents = fullLife / 100;
	int dec = (fullLife - cents * 100) / 10;
	int unid = (fullLife - cents * 100 - dec * 10);

	// Crear los numeros de vida
	for (int i = 0; i < 7; i++) {
		GameObject* number = new GameObject();
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 + 60 + (12 * i), 46), Vector2D(), 9, 18, 0);
		
		auto anim = number->addComponent<Animator>(SDLApplication::getTexture("statisticsNumbers"), 9, 18, 6, 2);
		for (int j = 0; j < 11; j++) anim->createAnim(to_string(j), j, j, 1, 0);
		if (i == 0 || i == 4) anim->play(to_string(cents));
		else if (i == 1 || i == 5) anim->play(to_string(dec));
		else if (i == 2 || i == 6) anim->play(to_string(unid));
		else if (i == 3) anim->play(to_string(10));

		lifeCounter.push_back(number);
	}

	cents = fullMana / 100;
	dec = (fullMana - cents * 100) / 10;
	unid = (fullMana - cents * 100 - dec * 10);

	// Crear los numeros de maná
	for (int i = 0; i < 7; i++) {
		GameObject* number = new GameObject();
		number->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - 140 + (12 * i), 46), Vector2D(), 9, 18, 0);

		auto anim = number->addComponent<Animator>(SDLApplication::getTexture("statisticsNumbers"), 9, 18, 6, 2);
		for (int j = 0; j < 11; j++) anim->createAnim(to_string(j), j, j, 1, 0);
		if (i == 0 || i == 4) anim->play(to_string(cents));
		else if (i == 1 || i == 5) anim->play(to_string(dec));
		else if (i == 2 || i == 6) anim->play(to_string(unid));
		else if (i == 3) anim->play(to_string(10));

		manaCounter.push_back(number);
	}
}

// Crea la barra de vida
void StatisticsUI::createLifeBar(int value) {
	healthBar = new GameObject();
	healthBar->addComponent<Transform>(LIFEBAR_POSITION, Vector2D(), BAR_WIDTH * 2.5, BAR_HEIGHT * 2.5);
	auto anim = healthBar->addComponent<Animator>(SDLApplication::getTexture(LIFEBAR), BAR_WIDTH, BAR_HEIGHT, 4, 3);
	anim->attachToCamera();
	anim->createAnim(LIFEBAR, 0, 10, 5, -1);
	anim->play(LIFEBAR);
	healthBar->addComponent<BarComponent>(true, value);
}

// Crea la barra de mana
void StatisticsUI::createManaBar(int value) {
	manaBar = new GameObject();
	manaBar->addComponent<Transform>(MANABAR_POSITION, Vector2D(), BAR_WIDTH * 2.5, BAR_HEIGHT * 2.5);
	auto anim = manaBar->addComponent<Animator>(SDLApplication::getTexture(MANABAR), BAR_WIDTH, BAR_HEIGHT, 4, 3);
	anim->attachToCamera();
	anim->createAnim(MANABAR, 0, 10, 5, -1);
	anim->play(MANABAR);
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

void StatisticsUI::OnHealthChanges(float value) {
	float newSrcRectFactor = (100 * value) / (fullLife * 100);
	healthBar->getComponent<Animator>()->setSrcRectRelativeWidth(newSrcRectFactor);
	// healthBar->getComponent<BarComponent>()->changeBar(value);
}

void StatisticsUI::OnManaChanges(float value) {
	float newSrcRectFactor = (100 * value) / (fullMana * 100);
	manaBar->getComponent<Animator>()->setSrcRectRelativeWidth(newSrcRectFactor);
	manaBar->getComponent<BarComponent>()->changeBar(value);
}