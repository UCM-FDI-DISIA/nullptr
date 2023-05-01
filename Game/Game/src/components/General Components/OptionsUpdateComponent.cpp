#include "OptionsUpdateComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../scenes/OptionsMenuScene.h"
#include "../General Components/TextComponent.h"

// Constructora
OptionsUpdateComponent::OptionsUpdateComponent(OptionId option_) : option(option_), peripheral(false), optionsMenuScene(nullptr) {}

// Destructora
OptionsUpdateComponent::~OptionsUpdateComponent() {}

// Inicializa el componente
void OptionsUpdateComponent::initComponent() {
	optionsMenuScene = dynamic_cast<OptionsMenuScene*>(gStt);
}

// Actualiza los valores de las opciones
void OptionsUpdateComponent::update() {
	switch (option) {
	case _option_PERIPHERAL: 
		// Si se conecta y el mensaje de conexion de gamepad esta activo, se actualiza
		if (ih().isControllerConnected() && peripheral) {

#ifdef _DEBUG
			cout << "Actualiza la conexion del gamepad" << endl;
#endif
			optionsMenuScene->updateGamepadConnection();

			peripheral = false;
		}
	break;
	}
}