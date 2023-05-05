#pragma once
#include "../Component.h"
#include "../../gameObjects/GameObject.h"
#include "Transform.h"
#include "../../scenes/GameState.h"
#include "TextComponent.h"

class PopupComponent : public Component {
private:
	Transform* tr;
	GameObject* frame;
	GameObject* name;
	GameObject* desc;
	GameObject* stats;
	//GameObject* weapon;
	Relic* rel;

	bool over;

public:
	static const int id = _POPUP_COMPONENT;

	PopupComponent(Relic* r) : Component(), rel(r), over(false), frame(nullptr), name(nullptr),
		desc(nullptr), stats(nullptr) {};

	virtual void initComponent();

	virtual void update();

	void createRelicFrame();
	void quitFrame();

	string getUpgradesString(Relic* r);
};