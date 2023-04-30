#pragma once
#include "GameState.h"
#include <unordered_map>

class SDLApplication;
class OptionsMenuScene : public GameState, public Singleton<OptionsMenuScene> {
	friend Singleton<OptionsMenuScene>; 
private:
	// 1er GameObject* corresponde al objeto de texto del nombre del control
	// 2o GameObject* corresponde al objeto de texto de la opcion actual del control
	// 3o int corresponde al numero de la opcion actual
	pair<GameObject*, pair<GameObject*, int>> music;
	pair<GameObject*, pair<GameObject*, int>> fx;
	pair<GameObject*, pair<GameObject*, int>> fullWindow;
	pair<GameObject*, pair<GameObject*, int>> peripheral;
	// Botones de cambio de opciones de los controles
	Button* musicLeftButton;
	Button* musicRightButton;
	Button* fxLeftButton;
	Button* fxRightButton;
	Button* fullWindowLeftButton;
	Button* fullWindowRightButton;
	Button* peripheralLeftButton;
	Button* peripheralRightButton;
	// Listas con las opciones y sus respectivos callbacks
	vector<pair<string, CallBack>> musicOptions;
	vector<pair<string, CallBack>> fxOptions;
	vector<pair<string, CallBack>> fullWindowOptions;
	vector<pair<string, CallBack>> peripheralOptions;
	// Mapa que como clave tiene el 1er GameObject* de los anteriores y como valor tiene
	// otro mapa que contiene como clave el numero de la opcion y como valor tiene 
	// una pareja: string corresponde al valor de texto que tiene la opcion y CallBack,
	// su respectiva funcion a llamar
	unordered_map<GameObject*, unordered_map<int,pair<string, CallBack>>> controls;

	GameObject* gamepadConnection;
public:
	// Constructora
	OptionsMenuScene();
	// Destructora
	~OptionsMenuScene();
	// Anade el fondo
	void addBackground();
	// Crea un conjunto de control con titulo y flechas
	void createControl(string title, pair<GameObject*, pair<GameObject*, int>>& control, OptionId optionId, SDL_Rect controlRect,
		Button*& leftButton, Button*& rightButton, vector<pair<string, CallBack>>& options);
	// Cambia a la opcion de la izquierda y ejecuta su callback
	void leftOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
	// Cambia a la opcion de la derecha y ejecuta su callback
	void rightOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
	// Muestra una opcion de entre las que tenga el objeto
	void showOption(pair<GameObject*, pair<GameObject*, int>>& control, Button* leftButton, Button* rightButton, SDL_Rect controlRect);
	// Muestra un feedback para conectar un mando
	void showGamepadConnection();
	// Quita el feedback de conectar un mando
	void hideGamepadConnection();
	// Si se detecta que se ha conectado un mando mientras está en estado de espera del mando, actualiza
	void updateGamepadConnection();
	// Devuelve el objeto de texto gamepadConnection
	inline GameObject* getGamepadConnection() { return gamepadConnection; }
	// Devuelve el periferico
	inline pair<GameObject*, pair<GameObject*, int>> getPeripheral() { return peripheral; }
	// Carga las opciones guardadas desde json
	void loadOptionsFromJSON();
	// Guarda las opciones en el json
	void saveOptionsToJSON();
};