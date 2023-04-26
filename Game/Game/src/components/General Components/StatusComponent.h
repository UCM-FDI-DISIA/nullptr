#pragma once
#include "../Component.h"
#include "HealthComponent.h"
#include "EffectController.h"
#include "../Enemy components/EnemyBehaviour.h"
#include "../../gameObjects/GameObject.h"
#include <unordered_map>

// Este componente sirve para manejar todos los eventos relacionados con
// los estados alterados como la confusion o la quemadura
class StatusComponent : public Component {
public:
	enum status {
		NONE,
		CONFUSED,
		BURNED,
		LAST_STATUS
	};
private:
	HealthComponent* health;
	EnemyBehaviour* enemyAI;
	EffectController* eController;
	unordered_map<status, float> statusMap;
	int aSecond;
public:
	static const int id = _STATUS;
	StatusComponent();
	void initComponent() override;
	void update() override;
	void applyStatus(status status, float duration);
};
