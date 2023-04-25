#include "BarComponent.h"
#include "../../scenes/BattleScene.h"

// Constructor para man�
BarComponent::BarComponent(int _currentCuantity) : 
	currentCuantity(_currentCuantity), tr(nullptr) {

	countDownSound = &sdlutils().soundEffects().at(Constant::getString("LOAD_EXIT_SOUND"));
}

// Inicializar componente
void BarComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void BarComponent::onManaChanges(float value, float maxValue, vector<GameObject*>& myNumbers) {
	// Cambiar el tama�o de la animaci�n respecto al man� gastado
	changeAnimatorSrcRelativeWidth(gObj, maxValue, value);

	// Cambiar los n�meros para mostrar el mana actual
	changeNumbers(myNumbers, value);

	// Reposicionar la barra correctament
	if (value != currentCuantity) {
		//Calculo la diferencia y me guardo la longitud original de la barra
		int dif = value - currentCuantity;
		int prevW = tr->getWidth();
		//La nueva longitud
		if (prevW + dif <= 0) {
			tr->setWidth(1);
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (prevW - 1));
		}
		else {
			//tr->setWidth(prevW + (dif * 2));
			//Me guardo la coordenada en X original y seteo una nueva en consecuencia al cambio
			int prevX = tr->getPos().getX();
			tr->setX(prevX - (dif * 2));
			currentCuantity = value;
		}
	}
}

void BarComponent::onHealthChanges(float value, float maxValue, vector<GameObject*>& myNumbers) {
	if (value > 0) {
		// Cambiar el tama�o de la animaci�n respecto a la vida restante
		changeAnimatorSrcRelativeWidth(gObj, maxValue, value);

		// Cambiar los n�meros para mostrar la vida actual
		changeNumbers(myNumbers, value);
	}
	else {
		// Cambiar el tama�o de la animaci�n
		changeAnimatorSrcRelativeWidth(gObj, maxValue, 1);

		// Cambiar los n�meros para mostrar la vida nula 
		changeNumbers(myNumbers, 0);

		// Descativar barra
		gObj->setAlive(false);
	}
}

void BarComponent::onEtherChanges(float value, vector<GameObject*>& myNumbers) {
	// Cambiar el tama�o de la animaci�n respecto al man� gastado
	changeAnimatorSrcRelativeHeight(gObj, 100, value);

	// Cambiar los n�meros para mostrar el �ter recogido actual
	changeNumbers(myNumbers, value);
}

// Cambia el valor de los n�meros activan su animaci�n correspondiente
void BarComponent::changeNumbers(vector<GameObject*>& vect, int value) {
	// Obtener unidades
	tuple<cents, decs, unids> units = getUnits(value);

	// 0 centenas - 1 decenas - 2 unidades
	vect[0]->getComponent<Animator>()->play(to_string(get<0>(units)));
	vect[1]->getComponent<Animator>()->play(to_string(get<1>(units)));
	vect[2]->getComponent<Animator>()->play(to_string(get<2>(units)));
}

// Cambia el valor de los n�meros activan su animaci�n correspondiente
void BarComponent::changeEtherNumbers(GameObject* num, int value) {
	num->getComponent<Animator>()->play(to_string(value));
	//Sonido
	countDownSound->play();
}

// Devuelve una tupla con el valor de las centenas, las decenas y las unidades
tuple<cents, decs, unids> BarComponent::getUnits(int value) {
	int cents = value / 100;
	int decs = (value - cents * 100) / 10;
	int unids = (value - cents * 100 - decs * 10);

	return make_tuple(cents, decs, unids);
}

// C�lcula y cambia el ancho de animaci�n al correspondiente
void BarComponent::changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value) {
	bar->getComponent<Animator>()->setSrcRectRelativeWidth(getFactored(maxValue, value));
}

// C�lcula y cambia el alto de animaci�n al correspondiente
void BarComponent::changeAnimatorSrcRelativeHeight(GameObject* meter, float maxValue, float value) {
	meter->getComponent<Animator>()->setSrcRectRelativeHeight(getFactored(maxValue, value));
}

// Devuelve en 0.XX el valor del factor que usar en el animator
float BarComponent::getFactored(float maxValue, float value) {
	return value / maxValue;
}