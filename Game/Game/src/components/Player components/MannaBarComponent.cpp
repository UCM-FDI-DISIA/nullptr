#include "MannaBarComponent.h"
#include "../../scenes/BattleScene.h"

MannaBarComponent::MannaBarComponent(CardComponent* _info) : currentManna(0), info(_info), tr(nullptr) { }

void MannaBarComponent::initComponent() {
	//info = dynamic_cast<BattleScene*>(gStt)->getPlayer()->getComponent<CardComponent>();
	currentManna = info->getMana();
	tr = gObj->getComponent<Transform>();
}

void MannaBarComponent::changeBar() {
	//Si la cantidad de maná ha cambiado
	if (info->getMana() != currentManna) {
		//Calculo la diferencia y me guardo la longitud original de la barra
		int dif = info->getMana() - currentManna;
		int prevW = tr->getWidth();
		//La nueva longitud
		if (prevW + dif <= 0) {
			tr->setWidth(1);
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (prevW - 1));
		}
		else {
			tr->setWidth(prevW + (dif * 2));
			//Me guardo la coordenada en X original y seteo una nueva en consecuencia al cambio
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (dif * 2));
			currentManna = info->getMana();
		}
	}
}