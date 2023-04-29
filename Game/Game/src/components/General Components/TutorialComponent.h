#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"


enum Pasos {
	Movimiento, Carta, Mano, Enemigos, Habilidad, Portal, Introduccion
};

class TutorialScene;
class TutorialComponent : public Component {
private:
	vector<pair<CallBack, double>> steps;
	CallBack activatePopup;
	Pasos current;
	TutorialScene* ts;
	float timeOffset;
	bool firstActionDone, canCount, discarted, newHand, ability, canAdvance;
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
	inline void setAbility(bool value) { ability = value; }
	inline bool getCanCount() { return canCount; }
	inline void doStep() { steps[current].first(); }
	inline bool getCanAdvance() { return canAdvance; }
	inline void setCanAdvance(bool value) { canAdvance = value; }

	inline void setCurrentStep(Pasos nStep) { current = nStep; }
};