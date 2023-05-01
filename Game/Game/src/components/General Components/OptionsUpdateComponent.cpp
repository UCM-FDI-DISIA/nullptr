#include "OptionsUpdateComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../scenes/OptionsMenuScene.h"
#include "../General Components/TextComponent.h"

// Constructora
OptionsUpdateComponent::OptionsUpdateComponent(OptionId option_) : option(option_), peripheral(false) {}

// Destructora
OptionsUpdateComponent::~OptionsUpdateComponent() {}

// Inicializa el componente
void OptionsUpdateComponent::initComponent() {}

// Actualiza los valores de las opciones
void OptionsUpdateComponent::update() {
	switch (option) {
	case _option_MUSIC: break;
	case _option_SFX: break;
	case _option_FULLWINDOW: break;
	case _option_PERIPHERAL: 
		// Si se conecta y el mensaje de conexion de gamepad esta activo, se actualiza
		// POR QUE ES NULO
		if (ih().isControllerConnected() && peripheral) {

#ifdef _DEBUG
			cout << "Actualiza la conexion del gamepad" << endl;
#endif
			dynamic_cast<OptionsMenuScene*>(gStt)->updateGamepadConnection();

			peripheral = false;
		}
	break;
	}
}