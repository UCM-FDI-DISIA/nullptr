#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"


enum Pasos {
	Movimiento, Carta, Descarte, Enemigos, Habilidad, Drops, Portal
};

class TutorialScene;
class TutorialComponent : public Component {
private:
	TutorialScene* ts;
	Pasos current;
	float startime, timeOffset;

public:
	// Identificador
	static const int id = _TUTORIAL_COMPONENT;
	// Constructora
	TutorialComponent(TutorialScene* _t);
	// Inicializa el componente
	void initComponent();
	// Actualiza la escena
	void update();
};