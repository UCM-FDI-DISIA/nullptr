#pragma once

#include <map>
#include "GameControl.h"
class ButtonNavigator {
private:
	enum direction : int {
		horizontal, vertical
	};
	enum way : int {
		u, d, l, r
	};
	struct ButtonData;
	typedef std::map<int, ButtonData> button_map;
public:
	struct ButtonData {
		button_map::iterator pos[4];
		int mousePos[2];
		void setPos(int i, button_map::iterator it) { pos[i] = it; };
	};
private:

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

