#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/OptionsUpdateComponent.h"

// Constructora
OptionsMenuScene::OptionsMenuScene() : music(make_tuple(nullptr, nullptr, 0, nullptr, nullptr)), sfx(make_tuple(nullptr, nullptr, 0, nullptr, nullptr)), fullWindow(make_tuple(nullptr, nullptr, 0, nullptr, nullptr)), peripheral(make_tuple(nullptr, nullptr, 0, nullptr, nullptr)),
gamepadConnection(nullptr) {

	// Fondo
	addBackground();

	// Boton de salida
	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::popGameState(); }, Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH - 50, WIN_HEIGHT - MM_BUTTON_HEIGHT - 50), aI, -1, nullptr, 2.0f)->setAsDefaultButton();

	// Anade todas las opciones
	addOptions();

	// Carga opciones si se hubieran cambiado en algun momento
	loadOptions();

	createControl("MUSICA", music, OptionId::_option_MUSIC, MUSIC_RECT);
	createControl("EFECTOS DE SONIDO", sfx, OptionId::_option_SFX, FX_RECT);
	createControl("PANTALLA COMPLETA", fullWindow, OptionId::_option_FULLWINDOW, FULL_WINDOW_RECT);
	createControl("CONTROL", peripheral, OptionId::_option_PERIPHERAL, PERIPHERAL_RECT);
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

// Anade las opciones de los controles
void OptionsMenuScene::addOptions() {

	get<0>(music) = addGameObject(_grp_OPTIONS);
	controls[get<0>(music)][0] = {"0", []() { Mix_VolumeMusic(0); }};
	controls[get<0>(music)][1] = { "25", []() { Mix_VolumeMusic(MIX_MAX_VOLUME / 4); } };
	controls[get<0>(music)][2] = { "50", []() { Mix_VolumeMusic(MIX_MAX_VOLUME / 2); } };
	controls[get<0>(music)][3] = { "75", []() { Mix_VolumeMusic(MIX_MAX_VOLUME * 2 / 3); } };
	controls[get<0>(music)][4] = { "100", []() { Mix_VolumeMusic(MIX_MAX_VOLUME); } };

	get<0>(sfx) = addGameObject(_grp_OPTIONS);
	controls[get<0>(sfx)][0] = { "0", []() { Mix_MasterVolume(0); } };
	controls[get<0>(sfx)][1] = { "25", []() { Mix_MasterVolume(MIX_MAX_VOLUME / 4); } };
	controls[get<0>(sfx)][2] = { "50", []() { Mix_MasterVolume(MIX_MAX_VOLUME / 2); } };
	controls[get<0>(sfx)][3] = { "75", []() { Mix_MasterVolume(MIX_MAX_VOLUME * 2 / 3); } };
	controls[get<0>(sfx)][4] = { "100", []() { Mix_MasterVolume(MIX_MAX_VOLUME); } };

	get<0>(fullWindow) = addGameObject(_grp_OPTIONS);
	controls[get<0>(fullWindow)][0] = { "NO", []() {
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, 0);
		}
	} };
	controls[get<0>(fullWindow)][1] = { "SI", []() {
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (!(flags & SDL_WINDOW_FULLSCREEN)) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	} };

	get<0>(peripheral) = addGameObject(_grp_OPTIONS);
	controls[get<0>(peripheral)][0] = { "TECLADO + RATON", [&]() { hideGamepadConnection(); gmCtrl().changeToKeyboard(); } };
	controls[get<0>(peripheral)][1] = { "MANDO", [&]() { if (ih().isControllerConnected()) { gmCtrl().changeToGamepad(); }
		else {
		// Si el mando no esta conectado pero esta seleccionado el modo mando, 
		// aparece el texto de conectar el mando y se mantiene a la espera de
		// la conexion del mando desde el OptionsUpdateComponent del peripheral
		showGamepadConnection();

		OptionsUpdateComponent* oUC = get<0>(peripheral)->getComponent<OptionsUpdateComponent>();
		if (oUC != nullptr) oUC->setPeripheral(true);
	}
	} };
}


// Crea un conjunto de control con titulo y flechas
void OptionsMenuScene::createControl(string title, tuple<GameObject*, GameObject*, int, Button*, Button*>& control, OptionId optionId, SDL_Rect controlRect) {

	// Anade el titulo
	get<0>(control)->addComponent<Transform>(Vector2D(controlRect.x, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	get<0>(control)->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), title);
	get<0>(control)->addComponent<OptionsUpdateComponent>(optionId);

	get<3>(control) = createLeftArrow([&, optionId]() { leftOption(control, optionId, controlRect); }, controlRect);
	get<4>(control) = createRightArrow([&, optionId]() { rightOption(control, optionId, controlRect); }, controlRect);

	// Se llama a su callback
	controls[get<0>(control)][get<2>(control)].second();

	// Muestra la opcion inicial
	showOption(control, optionId, getOptionRect(controlRect));
}

// Cambia a la opcion de la izquierda y ejecuta su callback
void OptionsMenuScene::leftOption(tuple<GameObject*, GameObject*, int, Button*, Button*> control, OptionId optionId, SDL_Rect controlRect) {
	if (!(get<2>(control) == 0 && (optionId == _option_MUSIC || optionId == _option_SFX))) {
		--get<2>(control);

		// Si se trataba de la primera opcion, se coloca la ultima opcion
		if (get<2>(control) < 0) get<2>(control) = controls[get<0>(control)].size() - 1;
		// Se llama a su callback
		controls[get<0>(control)][get<2>(control)].second();

		showOption(control, optionId, controlRect);
	}
}

// Cambia a la opcion de la derecha y ejecuta su callback
void OptionsMenuScene::rightOption(tuple<GameObject*, GameObject*, int, Button*, Button*> control, OptionId optionId, SDL_Rect controlRect) {
	if (!(get<2>(control) == 4 && (optionId == _option_MUSIC || optionId == _option_SFX))) {
		++get<2>(control);

		// Si se trataba de la ultima opcion, se coloca la primera
		if (get<2>(control) > controls[get<0>(control)].size() - 1) get<2>(control) = 0;
		// Se llama a su callback
		controls[get<0>(control)][get<2>(control)].second();

		showOption(control, optionId, controlRect);
	}
}

// Muestra una opcion de entre las que tenga el objeto
void OptionsMenuScene::showOption(tuple<GameObject*, GameObject*, int, Button*, Button*> control, OptionId optionId, SDL_Rect controlRect) {

	// Anade el texto de la opcion
	string optionString = controls[get<0>(control)][get<2>(control)].first;
	if (get<1>(control) == nullptr) get<1>(control) = addGameObject();
	get<1>(control)->addComponent<Transform>(Vector2D(controlRect.x + controlRect.w / 2 - 10 * optionString.size() / 2, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	get<1>(control)->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), optionString);
	
	switch (optionId) {
	case _option_MUSIC: get<2>(music) = get<2>(control); break;
	case _option_SFX: get<2>(sfx) = get<2>(control); break;
	case _option_FULLWINDOW: get<2>(fullWindow) = get<2>(control); break;
	case _option_PERIPHERAL: get<2>(peripheral) = get<2>(control); break;
	}

	// Reescribe sus callbacks
	if (get<3>(control) != nullptr) {
		get<3>(control)->setCallBack([&, control, controlRect, optionId]() { leftOption(control, optionId, controlRect); });
	}
	if (get<4>(control) != nullptr) {
		get<4>(control)->setCallBack([&, control, controlRect, optionId]() { rightOption(control, optionId, controlRect); });
	}
}

// Crea una boton flecha
Button* OptionsMenuScene::createArrow(CallBack cb, Vector2D pos, AnimatorInfo aI) {
	return addGameObject<Button>(cb, pos, aI, ONOUT_OPTIONS_ARROW, ONOVER_OPTIONS_ARROW, ONCLICK_OPTIONS_ARROW);
}

// Crea un boton flecha izquierda
Button* OptionsMenuScene::createLeftArrow(CallBack cb, SDL_Rect controlRect) {

	SDL_Rect optionsRect = getOptionRect(controlRect);
	return createArrow(cb, Vector2D(optionsRect.x - 70, optionsRect.y), AnimatorInfo("LeftArrow", 64, 44, 32, 22, 1, 3));
}

// Crea un boton flecha derecha
Button* OptionsMenuScene::createRightArrow(CallBack cb, SDL_Rect controlRect) {
	SDL_Rect optionsRect = getOptionRect(controlRect);
	return createArrow(cb, Vector2D(optionsRect.x + optionsRect.w + 70, optionsRect.y), AnimatorInfo("RightArrow", 64, 44, 32, 22, 1, 3));
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
	get<2>(music) = oD().getMusic();
	get<2>(sfx) = oD().getSFX();
	get<2>(fullWindow) = oD().getFullWindow();
	get<2>(peripheral) = oD().getPeripheral();
}

// Guarda las opciones en el json
void OptionsMenuScene::saveOptions() {
	oD().setMusic(get<2>(music));
	oD().setSFX(get<2>(sfx));
	oD().setFullWindow(get<2>(fullWindow));
	if (ih().isControllerConnected()) oD().setPeripheral(get<2>(peripheral));
	else oD().setPeripheral(0);
}