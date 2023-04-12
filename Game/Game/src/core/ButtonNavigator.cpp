#include "ButtonNavigator.h"


ButtonNavigator::ButtonNavigator() : gmCtrl_(gmCtrl()) {}

void ButtonNavigator::up() {
	changePos(u);
}
void ButtonNavigator::down() {
	changePos(d);
}
void ButtonNavigator::left() {
	changePos(l);
}
void ButtonNavigator::right() {
	changePos(r);
}

void ButtonNavigator::changePos(way w) {
	(w % 2 == 0) ?
		++currentButton.pos[w] :
		--currentButton.pos[w];


	currentButton.mousePos[horizontal] = currentButton.pos[w]->second.mousePos[horizontal];
	currentButton.mousePos[vertical] = currentButton.pos[w]->second.mousePos[vertical];
	for (int i = 0; i < 4; ++i) {
		if (i != w) currentButton.pos[i] = currentButton.pos[w]->second.pos[i];
	}

	gmCtrl_.moveMouse(currentButton.mousePos[horizontal], currentButton.mousePos[vertical]);
}

ButtonData ButtonNavigator::insert(SDL_Rect r) {
	return insert(r.x, r.y, r.w, r.h);
}

// recibe posicion y tamaño del botón con el componente
ButtonData ButtonNavigator::insert(int x, int y, int w, int h) {
	// area total en el map
	x -= w;
	y -= h;
	w *= 4;
	h *= 4;
	// sacar los 4 bordes
	int up[2] = { x + w / 2, y };
	int down[2] = { x + w / 2, y + h };
	int left[2] = { x, y + h / 2 };
	int right[2] = { x + w, y + h / 2 };

	ButtonData bd;
	bd.mousePos[horizontal] = x + w / 2;
	bd.mousePos[vertical] = y + h / 2;
	std::pair<button_map::iterator, bool> its[4];
	its[u] = matrix[vertical][up[1]].insert({ up[0], bd });
	its[d] = matrix[vertical][down[1]].insert({ down[0] , bd });
	its[l] = matrix[horizontal][left[0]].insert({ left[1], bd });
	its[r] = matrix[horizontal][right[0]].insert({ right[1], bd });
	for (int i = 0; i < 4; ++i)
		bd.pos[i] = its[i].first;

	// insertar en todo el área del botón del map
	for (int i = x; i < x + w; ++i) {
		for (int j = y; j < y + h; ++j) {
			matrix[horizontal][x].insert({ y, bd });
			matrix[vertical][y].insert({ x, bd });
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (its[i].second) {
			for (int j = 0; j < 4; ++j)
				if (i != j) its[i].first->second.pos[j] = its[j].first;
		}
	}

	return bd;
}


void ButtonNavigator::setCurrentButton(ButtonData bd) {
	currentButton = bd;
}