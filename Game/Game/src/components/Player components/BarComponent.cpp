#include "BarComponent.h"
#include "../../scenes/BattleScene.h"

// Constructor para maná
BarComponent::BarComponent(bool _isLifeBar, int _currentCuantity) : 
	currentCuantity(_currentCuantity), tr(nullptr), isLifeBar(_isLifeBar) { }

void BarComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void BarComponent::changeBar(int changeValue) {
	//Si la cantidad de maná ha cambiado
	if (!isLifeBar) processManaChange(changeValue);
	else processLifeChange(changeValue);
}

void BarComponent::processManaChange(int cuantity) {
	if (cuantity != currentCuantity) {
		//Calculo la diferencia y me guardo la longitud original de la barra
		int dif = cuantity - currentCuantity;
		int prevW = tr->getWidth();
		//La nueva longitud
		if (prevW + dif <= 0) {
			tr->setWidth(0.1);
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (prevW - 1));
		}
		else {
			//tr->setWidth(prevW + (dif * 2));
			//Me guardo la coordenada en X original y seteo una nueva en consecuencia al cambio
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (dif * 2 - 2));
			currentCuantity = cuantity;
		}
	}
}

void BarComponent::processLifeChange(int cuantity) {

}