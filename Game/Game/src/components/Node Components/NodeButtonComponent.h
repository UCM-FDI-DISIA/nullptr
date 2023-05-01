#pragma once
#include "../General Components/ButtonComponent.h"
#include "../../gameObjects/Node Objects/Node.h"

class NodeButtonComponent : public ButtonComponent {
private:
	nodeState const& nState;
	float horizontalMult;
public:
	// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
	NodeButtonComponent(CallBack _f, nodeState const& _nState, float navigatorHorizontalMult);

	void initComponent() override;

	// Actualiza la animación del botón según el estado
	virtual void updateAnimation();

	// Ejecuta el callback del botón si este está disponible
	virtual void onClick();
	
};
