#include "PopupComponent.h"

void PopupComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void PopupComponent::update() {
	// Posición del ratón
	int x; int y;
	SDL_GetMouseState(&x, &y);

	Vector2D pos = tr->getPos();
	int width = tr->getWidth();
	int height = tr->getHeight();

	if (pos.getX() <= x && pos.getX() + width >= x  && pos.getY() <= y && pos.getY() + height >= y) {
		if (rel != nullptr && !over) {
			createRelicFrame();
			over = true;
		}
	}
	else over = false;

	if (!over) quitFrame();
}

void PopupComponent::createRelicFrame() {
	Vector2D objPos = tr->getPos();
	cout << "hola" << endl;

	// Frame
	frame = gStt->addGameObject(_grp_UI);
	Transform* trFrame = frame->addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, 100, 100);
	frame->addComponent<Image>(&sdlutils().images().at("PopupFrame"))->attachToCamera();

	// Nombre
	name = gStt->addGameObject(_grp_UI);
	Transform* trName = name->addComponent<Transform>(objPos - Vector2D(35, 0), VECTOR_ZERO, 100, 100);
	name->addComponent<TextComponent>(&sdlutils().fonts().at(FONT_SS_REG22), rel->id, COLOR_WHITE)->attachToCamera();
	trName->setPos(trName->getPos() - Vector2D(trName->getWidth() + 20, trName->getHeight() / 2));
	
	// Descripción
	desc = gStt->addGameObject(_grp_UI);
	Transform* trDesc = desc->addComponent<Transform>(trName->getPos() - Vector2D(trName->getWidth() / 8, -(trName->getHeight() + 5)),
		VECTOR_ZERO, trName->getWidth() + 50, trName->getHeight() + 50);
	desc->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR16"), rel->description, COLOR_WHITE, true)->attachToCamera();

	// Upgrades
	string upgrades = "";
	if (rel->health > 0) upgrades += ">Vida: +" + to_string((int)rel->health) + "\n";
	if (rel->mana > 0) upgrades += ">Mana: +" + to_string((int)rel->mana) + "\n";
	if (rel->speed > 0) upgrades += ">Velocidad: +" + to_string((int)rel->speed) + "\n";
	if (rel->attackMult > 0) upgrades += ">Ataque: +" + to_string((int)rel->attackMult) + "\n";
	if (rel->fireRateMult > 0) upgrades += ">Cadencia: +" + to_string((int)rel->fireRateMult);

	stats = gStt->addGameObject(_grp_UI);
	Transform* trStats = stats->addComponent<Transform>(trDesc->getPos() + Vector2D(0, +trDesc->getHeight() + 10), VECTOR_ZERO, 200, 200);
	stats->addComponent<TextComponent>(&sdlutils().fonts().at("SILKSCREEN_REGULAR16"), upgrades, COLOR_WHITE, true)->attachToCamera();

	// Reposicionar frame
	trFrame->setPos(trName->getPos() - Vector2D(55, 20));
	trFrame->setWidth(trDesc->getWidth() + 50);
	trFrame->setHeight(trName->getHeight() + trDesc->getHeight() + trStats->getHeight() + 60);

	cout << "hola2" << endl;
}

void PopupComponent::quitFrame() {
	if (frame != nullptr) frame->setAlive(false);
	if (name != nullptr) name->setAlive(false);
	if (desc != nullptr) desc->setAlive(false);
	if (stats != nullptr) stats->setAlive(false);
	frame = nullptr;
	name = nullptr;
	desc = nullptr;
	stats = nullptr;
}