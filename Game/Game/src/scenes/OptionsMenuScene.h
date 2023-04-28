#pragma once
#include "GameState.h"
#include <unordered_map>

const SDL_Rect volumeRect = { WIN_WIDTH / 3 - 200 , WIN_HEIGHT / 3, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect fullWindowRect = { WIN_WIDTH / 3 - 200 , volumeRect.y + volumeRect.h + 10, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect peripheralRect = { WIN_WIDTH / 3 - 200 , fullWindowRect.y + fullWindowRect.h + 10, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };

class SDLApplication;
class OptionsMenuScene : public GameState {
private:
	GameObject* background;
	// 1er GameObject* corresponde al objeto de texto del nombre del control
	// 2o GameObject* corresponde al objeto de texto de la opcion actual del control
	// 3o int corresponde al numero de la opcion actual
	pair<GameObject*, pair<GameObject*, int>> volume;
	pair<GameObject*, pair<GameObject*, int>> fullWindow;
	pair<GameObject*, pair<GameObject*, int>> peripheral;
	// Botones de cambio de opciones de los controles
	Button* volumeLeftButton;
	Button* volumeRightButton;
	Button* fullWindowLeftButton;
	Button* fullWindowRightButton;
	Button* peripheralLeftButton;
	Button* peripheralRightButton;
	// Mapa que como clave tiene el 1er GameObject* de los anteriores y como valor tiene
	// otro mapa que contiene como clave el numero de la opcion y como valor tiene 
	// una pareja: string corresponde al valor de texto que tiene la opcion y CallBack,
	// su respectiva funcion a llamar
	unordered_map<GameObject*, unordered_map<int,pair<string, CallBack>>> controls;

public:
	// Constructora
	OptionsMenuScene();
	// Destructora
	~OptionsMenuScene();
	// Anade el fondo
	void addBackground();
	// Crea un conjunto de control con titulo y flechas
	void createControl(string title, pair<GameObject*, pair<GameObject*, int>> control, SDL_Rect controlRect, 
		Button* leftButton, Button* rightButton, int numStrings, ...);
	// Cambia a la opcion de la izquierda y ejecuta su callback
	void leftOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
	// Cambia a la opcion de la derecha y ejecuta su callback
	void rightOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
	// Muestra una opcion de entre las que tenga el objeto
	void showOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
};