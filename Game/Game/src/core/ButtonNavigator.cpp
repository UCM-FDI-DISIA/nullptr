#include "ButtonNavigator.h"


// Constructora
ButtonNavigator::ButtonNavigator() : gmCtrl_(gmCtrl()), unlockedMovement_(true) {}

// Selecciona el botón adjacente al actual en la dirección indicada
void ButtonNavigator::changePos(way w) {
	if (unlockedMovement_) {
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
}

// Selecciona el botón encima del actual
void ButtonNavigator::up() {
	changePos(u);
}
// Selecciona el botón debajo del actual
void ButtonNavigator::down() {
	changePos(d);
}
// Selecciona el botón a la derecha del actual
void ButtonNavigator::left() {
	changePos(l);
}
// Selecciona el botón a la izquierda del actual
void ButtonNavigator::right() {
	changePos(r);
}

// Añade un botón al sistema de navegación entre estos, recibe su componente Imagen
ButtonData ButtonNavigator::insert(Image* im, float horMul) {
	SDL_Rect rr = im->getRect();
	SDL_Rect orr = rr;

	ButtonData bd;
	bd.buttonIm = im;

	rr.x /= 12;
	rr.y /= 12;
	rr.w /= 12;
	rr.w *= horMul;
	rr.h /= 12;

	// area total en el map
	rr.x -= rr.w/2;
	rr.y -= rr.h/2;
	rr.w *= 2;
	rr.h *= 2;
	// sacar los 4 bordes
	int up[2] = { rr.x + rr.w / 2, rr.y };
	int down[2] = { rr.x + rr.w / 2, rr.y + rr.h };
	int left[2] = { rr.x, rr.y + rr.h / 2 };
	int right[2] = { rr.x + rr.w, rr.y + rr.h / 2 };

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
	for (int i = rr.x; i < rr.x + rr.w; ++i) {
		for (int j = rr.y; j < rr.y + rr.h; ++j) {
			if (j > orr.y && j < orr.y + orr.h) matrix[d_x][i][j] = bd;
			else matrix[d_x][i].insert({ j, bd });
			
			if (i > orr.x && i < orr.x + orr.w) matrix[d_y][j][i] = bd;
			else matrix[d_y][j].insert({ i, bd });
		}
	}

	// 
	for (int i = 0; i < 4; ++i) {
		if (its[i].second) its[i].first->second = bd;
	}

	return ButtonData(bd);
}

// Recibe un botón y lo asigna como el actual
void ButtonNavigator::setCurrentButton(ButtonData bd) {
	currentButton = bd;

	SDL_Rect r = currentButton.buttonIm->getRect();
	gmCtrl_.moveMouse(r.x + r.w / 2, r.y + r.h / 2);
}

// Bloquea la navegacion entre botones
void ButtonNavigator::lockMovement() {
	unlockedMovement_ = false;
}
// Desbloquea la navegación entre botones
void ButtonNavigator::unlockMovement() {
	unlockedMovement_ = true;
}