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
	int dir = (w < 2) ? d_x : d_y;
	// incrementa
	if (w % 2 != 0) {
		if (std::next(currentButton.pos[w]) != matrix[dir][currentButton.supPos[w]].end()) {
			++currentButton.pos[w];
		}
	}
	// decrementa
	else {
		if (currentButton.pos[w] != matrix[dir][currentButton.supPos[w]].begin()) {
			--currentButton.pos[w];
		}
	}

	setCurrentButton(currentButton.pos[w]->second);
}

ButtonData ButtonNavigator::insert(SDL_Rect r) {
	return insert(r.x, r.y, r.w, r.h);
}

// recibe posicion y tamaño del botón con el componente
ButtonData ButtonNavigator::insert(int x, int y, int w, int h) {

	ButtonData bd;
	bd.mousePos[d_x] = x + w / 2;
	bd.mousePos[d_y] = y + h / 2;


	x /= 13;
	y /= 13;
	w /= 13;
	h /= 13;

	// area total en el map
	x -= w;
	y -= h;
	w *= 3;
	h *= 3;
	// sacar los 4 bordes
	int up[2] = { x + w / 2, y };
	int down[2] = { x + w / 2, y + h };
	int left[2] = { x, y + h / 2 };
	int right[2] = { x + w, y + h / 2 };

	// insertar laterales en el map
	std::pair<button_map::iterator, bool> its[4];
	its[u] = matrix[d_x][up[d_x]].insert({ up[d_y], bd });
	bd.supPos[u] = up[d_x];
	its[d] = matrix[d_x][down[d_x]].insert({ down[d_y] , bd });
	bd.supPos[d] = down[d_x];
	its[l] = matrix[d_y][left[d_y]].insert({ left[d_x], bd });
	bd.supPos[l] = left[d_y];
	its[r] = matrix[d_y][right[d_y]].insert({ right[d_x], bd });
	bd.supPos[r] = right[d_y];

	// asignar los laterales en el ButtonData
	for (int i = 0; i < 4; ++i) {
		bd.pos[i] = its[i].first;
	}

	// insertar en todo el área del botón del map
	for (int i = x; i < x + w; ++i) {
		for (int j = y; j < y + h; ++j) {
			matrix[d_x][i].insert({ j, bd });
			matrix[d_y][j].insert({ i, bd });
		}
	}

	// 
	for (int i = 0; i < 4; ++i) {
		if (its[i].second) 
			its[i].first->second = bd;
	}

	return ButtonData(bd);
}


void ButtonNavigator::setCurrentButton(ButtonData bd) {
	currentButton = bd;
	gmCtrl_.moveMouse(currentButton.mousePos[d_x], currentButton.mousePos[d_y]);
}