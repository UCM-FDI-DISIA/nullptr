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

	fullLife = life;
	fullMana = mana;
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