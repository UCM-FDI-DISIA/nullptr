#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/OptionsUpdateComponent.h"

// Constructora
OptionsMenuScene::OptionsMenuScene() : music({ nullptr, { nullptr, 0} }), sfx({ nullptr, { nullptr, 0} }), fullWindow({ nullptr, { nullptr, 0} }), peripheral({ nullptr, { nullptr, 0} }),
musicLeftButton(nullptr), musicRightButton(nullptr), sfxLeftButton(nullptr), sfxRightButton(nullptr), fullWindowLeftButton(nullptr), fullWindowRightButton(nullptr), peripheralLeftButton(nullptr), peripheralRightButton(nullptr),
gamepadConnection(nullptr) {

	// Fondo
	addBackground();

	// Boton de salida
	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::popGameState(); }, Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH - 50, WIN_HEIGHT - MM_BUTTON_HEIGHT - 50), aI, -1, nullptr, 2.0f)->setAsDefaultButton();

	musicOptions.push_back({ "50", []() { Mix_VolumeMusic(MIX_MAX_VOLUME / 2); } });
	musicOptions.push_back({ "75", []() { Mix_VolumeMusic(MIX_MAX_VOLUME * 2 / 3); } });
	musicOptions.push_back({ "100", []() { Mix_VolumeMusic(MIX_MAX_VOLUME); } });
	musicOptions.push_back({ "0", []() { Mix_VolumeMusic(0); } });
	musicOptions.push_back({ "25", []() { Mix_VolumeMusic(MIX_MAX_VOLUME / 4); } });

	sfxOptions.push_back({ "50", []() { Mix_MasterVolume(MIX_MAX_VOLUME / 2); } });
	sfxOptions.push_back({ "75", []() { Mix_MasterVolume(MIX_MAX_VOLUME * 2 / 3); } });
	sfxOptions.push_back({ "100", []() { Mix_MasterVolume(MIX_MAX_VOLUME); } });
	sfxOptions.push_back({ "0", []() { Mix_MasterVolume(0); } });
	sfxOptions.push_back({ "25", []() { Mix_MasterVolume(MIX_MAX_VOLUME / 4); } });
	

	fullWindowOptions.push_back({ "NO", []() {
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, 0);
		}
	}});
	fullWindowOptions.push_back({ "SI", []() { 
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (!(flags & SDL_WINDOW_FULLSCREEN)) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	} });

	peripheralOptions.push_back({ "TECLADO + RATON", [&]() { hideGamepadConnection(); gmCtrl().changeToKeyboard(); } });
	peripheralOptions.push_back({ "MANDO", [&]() { if (ih().isControllerConnected()) { gmCtrl().changeToGamepad(); }
		else { 
			// Si el mando no esta conectado pero esta seleccionado el modo mando, 
			// aparece el texto de conectar el mando y se mantiene a la espera de
			// la conexion del mando desde el OptionsUpdateComponent del peripheral
			showGamepadConnection(); 
	
			OptionsUpdateComponent* oUC = peripheral.first->getComponent<OptionsUpdateComponent>();
			if (oUC != nullptr) oUC->setPeripheral(true);

		} 
	} });

	loadOptions();

	createControl("MUSICA", music, OptionId::_option_MUSIC, MUSIC_RECT, musicLeftButton, musicRightButton, musicOptions);
	createControl("EFECTOS DE SONIDO", sfx, OptionId::_option_SFX, FX_RECT, sfxLeftButton, sfxRightButton, sfxOptions);
	createControl("PANTALLA COMPLETA", fullWindow, OptionId::_option_FULLWINDOW, FULL_WINDOW_RECT, fullWindowLeftButton, fullWindowRightButton, fullWindowOptions);
	createControl("CONTROL", peripheral, OptionId::_option_PERIPHERAL, PERIPHERAL_RECT, peripheralLeftButton, peripheralRightButton, peripheralOptions);
}

// Destructora
OptionsMenuScene::~OptionsMenuScene() { saveOptions(); }

// Anade el fondo
void OptionsMenuScene::addBackground() {
	// Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));
}

// Crea un conjunto de control con titulo y flechas
void OptionsMenuScene::createControl(string title, pair<GameObject*, pair<GameObject*, int>>& control, OptionId optionId, SDL_Rect controlRect, 
	Button*& leftButton, Button*& rightButton, vector<pair<string, CallBack>>& options) {

	// Anade el titulo
	control.first = addGameObject(_grp_OPTIONS);
	control.first->addComponent<Transform>(Vector2D(controlRect.x, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.first->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), title);
	control.first->addComponent<OptionsUpdateComponent>(optionId);

	// Anade las opciones con sus respectivos callbacks
	for (int i = 0; i < options.size(); ++i) {
		controls[control.first][i] = options[i];
	}

	SDL_Rect optionsRect = { controlRect.x + controlRect.w + 120, controlRect.y, 330, MM_BUTTON_HEIGHT };

	Animation onOut = Animation(0, 0, 7, -1);
	Animation onOver = Animation(1, 1, 7, -1);
	Animation onClick = Animation(2, 2, 7, -1);
	AnimatorInfo aI = AnimatorInfo("LeftArrow", 64, 44, 32, 22, 1, 3);
	leftButton = addGameObject<Button>([&]() { leftOption(control, leftButton, rightButton, controlRect); }, Vector2D(optionsRect.x - 70, optionsRect.y), aI, onOut, onOver, onClick);
	aI = AnimatorInfo("RightArrow", 64, 44, 32, 22, 1, 3);
	rightButton = addGameObject<Button>([&]() { rightOption(control, leftButton, rightButton, controlRect); }, Vector2D(optionsRect.x + optionsRect.w + 70, optionsRect.y), aI, onOut, onOver, onClick, -1, nullptr, 2.0f);

	// Se llama a su callback
	options[control.second.second].second();

	// Muestra la opcion inicial
	showOption(control, leftButton, rightButton, optionsRect);
}

// Cambia a la opcion de la izquierda y ejecuta su callback
void OptionsMenuScene::leftOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect) {
	--control.second.second;

	unordered_map<int, pair<string, CallBack>> options = controls[control.first];

	// Si se trataba de la primera opcion, se coloca la ultima opcion
	if (control.second.second < 0) control.second.second = options.size() - 1;
	// Se llama a su callback
	options[control.second.second].second();

	showOption(control, leftButton, rightButton, controlRect);
}

// Cambia a la opcion de la derecha y ejecuta su callback
void OptionsMenuScene::rightOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect) {
	++control.second.second;

	unordered_map<int, pair<string, CallBack>> options = controls[control.first];

	// Si se trataba de la ultima opcion, se coloca la primera
	if (control.second.second > options.size() - 1) control.second.second = 0;
	// Se llama a su callback
	options[control.second.second].second();

	showOption(control, leftButton, rightButton, controlRect);
}

// Muestra una opcion de entre las que tenga el objeto
void OptionsMenuScene::showOption(pair<GameObject*, pair<GameObject*, int>>& control, Button* leftButton, Button* rightButton, SDL_Rect controlRect) {
	string optionString = controls[control.first][control.second.second].first;
	if (control.second.first == nullptr) control.second.first = addGameObject();
	control.second.first->addComponent<Transform>(Vector2D(controlRect.x + controlRect.w / 2 - 10 * optionString.size() / 2, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.second.first->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), optionString);
	
	switch (control.first->getComponent<OptionsUpdateComponent>()->getOptionId()) {
	case _option_MUSIC: music.second.second = control.second.second; break;
	case _option_SFX: sfx.second.second = control.second.second; break;
	case _option_FULLWINDOW: fullWindow.second.second = control.second.second; break;
	case _option_PERIPHERAL: peripheral.second.second = control.second.second; break;
	}

	// Establece las flechas
	if (leftButton != nullptr) {
		leftButton->setCallBack([&, control, leftButton, rightButton, controlRect]() { leftOption(control, leftButton, rightButton, controlRect); });
	}
	if (rightButton != nullptr) {
		rightButton->setCallBack([&, control, leftButton, rightButton, controlRect]() { rightOption(control, leftButton, rightButton, controlRect); });
	}
}

// Muestra un feedback para conectar un mando
void OptionsMenuScene::showGamepadConnection() {
	// Mensaje de conexion del gamepad para dar feedback
	gamepadConnection = addGameObject();
	gamepadConnection->addComponent<Transform>(Vector2D(GAMEPAD_CONNECTION_RECT.x, GAMEPAD_CONNECTION_RECT.y), Vector2D(), GAMEPAD_CONNECTION_RECT.w, GAMEPAD_CONNECTION_RECT.h);
	gamepadConnection->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), GAMEPAD_CONNECTION_TEXT, build_sdlcolor("0xff000000"));
}

// Quita el feedback de conectar un mando
void OptionsMenuScene::hideGamepadConnection() {
	if (gamepadConnection != nullptr) {
		gamepadConnection->setAlive(false);
		gamepadConnection = nullptr;
	}
}

// Si se detecta que se ha conectado un mando mientras está en estado de espera del mando, actualiza
void OptionsMenuScene::updateGamepadConnection() {
	hideGamepadConnection();
	gmCtrl().changeControl();
}

// Carga las opciones guardadas desde json
void OptionsMenuScene::loadOptions() {
	music.second.second = oD().getMusic();
	sfx.second.second = oD().getSFX();
	fullWindow.second.second = oD().getFullWindow();
	peripheral.second.second = oD().getPeripheral();
}

// Guarda las opciones en el json
void OptionsMenuScene::saveOptions() {
	oD().setMusic(music.second.second);
	oD().setSFX(sfx.second.second);
	oD().setFullWindow(fullWindow.second.second);
	if (ih().isControllerConnected()) oD().setPeripheral(peripheral.second.second);
	else oD().setPeripheral(0);
}

// Reestablece los valores de las opciones
void OptionsMenuScene::resetOptions() {
	oD().resetOptions();
}