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
public:
	ButtonNavigator();

	void up();
	void down();
	void left();
	void right();

	void changePos(way w);

	// recibe componente imagen del botón
	ButtonData insert(Image* im);

	void setCurrentButton(ButtonData bd);
	void lockMovement();
	void unlockMovement();
};

