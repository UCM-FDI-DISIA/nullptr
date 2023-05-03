#pragma once
#include "../Component.h"

class OptionsMenuScene;
class OptionsUpdateComponent : public Component {
private:
	OptionsMenuScene* optionsMenuScene;
	OptionId option;
	bool peripheral;
public:
	// Identificador
	static const int id = _OPTIONSUPDATE;
	// Constructora
	OptionsUpdateComponent(OptionId option_);
	// Destructora
	virtual ~OptionsUpdateComponent();
	// Inicializa el componente
	virtual void initComponent();
	// Actualiza los valores de las opciones
	virtual void update();
	// Establece el periferico
	inline void setPeripheral(bool peripheral_) { peripheral = peripheral_; }

	// Devuelve la id de la opcion
	inline OptionId getOptionId() { return option; }
};