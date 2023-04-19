#pragma once

#include <map>
#include "GameControl.h"
#include "../components/General Components/Image.h"

struct ButtonData {
	std::map<int, ButtonData>::iterator pos[4];
	int supPos[4];
	Image* buttonIm;
};
enum direction : int {
	d_x = 0, d_y
};
enum way : int {
	u = 0, d, l, r
};

class ButtonNavigator {
private:
	typedef std::map<int, ButtonData> button_map;
	std::map<int, button_map> matrix[2];
	ButtonData currentButton;

	GameControl& gmCtrl_;
	bool unlockedMovement_;

	// Selecciona el botón adjacente al actual en la dirección indicada
	void changePos(way w);
public:
	// Constructora
	ButtonNavigator();
	// Selecciona el botón encima del actual
	void up();
	// Selecciona el botón debajo del actual
	void down();
	// Selecciona el botón a la derecha del actual
	void left();
	// Selecciona el botón a la izquierda del actual
	void right();


	// Añade un botón al sistema de navegación entre estos, recibe su componente Imagen
	ButtonData insert(Image* im, float horMul = 1, float verMul = 1);
	void erase(Image* im);

	// Recibe un botón y lo asigna como el actual
	void setCurrentButton(ButtonData bd);
	// Bloquea la navegacion entre botones
	void lockMovement();
	// Desbloquea la navegación entre botones
	void unlockMovement();
	// Comprueba si la imagen pasada es la del botón actual
	inline bool isCurrentButton(Image* im) { return im == currentButton.buttonIm; }
};

