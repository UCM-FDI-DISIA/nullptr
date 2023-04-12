#pragma once

#include <map>
#include "GameControl.h"


struct ButtonData {
	std::map<int, ButtonData>::iterator pos[4];
	int supPos[4];
	int mousePos[2];
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
public:
	ButtonNavigator();

	void up();
	void down();
	void left();
	void right();

	void changePos(way w);

	ButtonData insert(SDL_Rect r);

	// recibe posicion y tamaño del botón
	ButtonData insert(int x, int y, int w, int h);

	void setCurrentButton(ButtonData bd);
};

