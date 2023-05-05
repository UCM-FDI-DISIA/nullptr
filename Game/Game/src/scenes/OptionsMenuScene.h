#pragma once
#include "GameState.h"
#include <unordered_map>
#include <tuple>
#include "../data/OptionsData.h"

struct control {
	GameObject* titleText;
	GameObject* currentOptionText;
	int currentOption;
	Button* leftArrowButton;
	Button* rightArrowButton;
};

class SDLApplication;
class OptionsMenuScene : public GameState {
private:
	
	// Estas variables se encargan de guardar la informacion que se debe mostrar en pantalla
	control music;
	control sfx;
	control fullWindow;
	control peripheral;
	// Mapa que como clave tiene el 1er GameObject* de los anteriores y como valor tiene
	// otro mapa que contiene como clave el numero de la opcion y como valor tiene 
	// una pareja: string corresponde al valor de texto que tiene la opcion y CallBack,
	// su respectiva funcion a llamar
	// Este mapa se encarga de guardar los debidos strings y callbacks de cada opcion de cada control
	unordered_map<GameObject*, vector<pair<string, CallBack>>> controls;

	GameObject* gamepadConnection;
	const int nVolumeValues;
public:
	// Constructora
	OptionsMenuScene();
	// Destructora
	~OptionsMenuScene();
	// Anade el fondo
	void addBackground();
	// Anade las opciones de los controles
	void addOptions();
	// Crea un conjunto de control con titulo y flechas
	void createControl(string title, control& control, OptionId optionId, SDL_Rect controlRect);
	// Cambia a la opcion de la izquierda y ejecuta su callback
	void leftOption(control control, OptionId optionId, SDL_Rect controlRect);
	// Cambia a la opcion de la derecha y ejecuta su callback
	void rightOption(control control, OptionId optionId, SDL_Rect controlRect);
	// Muestra una opcion de entre las que tenga el objeto
	void showOption(control control, OptionId optionId, SDL_Rect controlRect);
	// Muestra un feedback para conectar un mando
	void showGamepadConnection();
	// Quita el feedback de conectar un mando
	void hideGamepadConnection();
	// Si se detecta que se ha conectado un mando mientras está en estado de espera del mando, actualiza
	void updateGamepadConnection();
	// Devuelve el objeto de texto gamepadConnection
	inline GameObject* getGamepadConnection() { return gamepadConnection; }
	// Devuelve el periferico
	inline control getPeripheral() { return peripheral; }
	// Crea una boton flecha
	Button* createArrow(CallBack cb, Vector2D pos, AnimatorInfo aI);
	// Crea un boton flecha izquierda
	Button* createLeftArrow(CallBack cb, SDL_Rect controlRect);
	// Crea un boton flecha derecha
	Button* createRightArrow(CallBack cb, SDL_Rect controlRect);
	// Devuelve el rect del texto de la opcion
	inline SDL_Rect getOptionRect(SDL_Rect controlRect) {
		return { controlRect.x + controlRect.w + 120, controlRect.y, 330, MM_BUTTON_HEIGHT };
	}
	// Carga las opciones guardadas desde json
	void loadOptions();
	// Guarda las opciones en el json
	void saveOptions();
};