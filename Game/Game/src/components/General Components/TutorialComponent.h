#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"


enum Pasos {
	Movimiento, Carta, Descarte, Enemigos, Habilidad, Drops, Portal, Introduccion
};

class TutorialScene;
class TutorialComponent : public Component {
private:
	vector<pair<CallBack, double>> steps;
	CallBack activatePopup;
	Pasos current;
	float timeOffset;
	bool firstActionDone, canCount, discarted, newHand;
public:
	// Identificador
	static const int id = _TUTORIAL_COMPONENT;
	// Constructora
	TutorialComponent(CallBack callback, vector<pair<CallBack, double>> steps);
	// Actualiza la escena
	void update();

	void changeState();
	inline void setDiscarted(bool value) { discarted = value; }
	inline void setNewHand(bool value) { newHand = value; }
	inline bool getCanCount() { return canCount; }
	inline void doStep() { steps[current].first(); }

	inline void setCurrentStep(Pasos nStep) { current = nStep; }
};