#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"


enum Pasos {
	Movimiento, Carta, Descarte, Enemigos, Habilidad, Drops, Portal
};

class TutorialScene;
class TutorialComponent : public Component {
private:
	vector<pair<CallBack, double>> steps;
	CallBack activatePopup;
	Pasos current;
	float startime, timeOffset;
	bool firstActionDone, canCount;
public:
	// Identificador
	static const int id = _TUTORIAL_COMPONENT;
	// Constructora
	TutorialComponent(CallBack callback, vector<pair<CallBack, double>> steps);
	// Actualiza la escena
	void update();

	void setCanCount();
	inline bool getCanCount() { return canCount; }
	inline void doStep() { steps[current].first(); }

	inline void setCurrentStep(Pasos nStep) { current = nStep; }
};