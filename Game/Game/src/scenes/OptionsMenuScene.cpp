#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include "../components/General Components/OptionsUpdateComponent.h"

// Constructora
OptionsMenuScene::OptionsMenuScene() : music({ nullptr, nullptr, 0, nullptr, nullptr }), sfx({ nullptr, nullptr, 0, nullptr, nullptr }), fullWindow({ nullptr, nullptr, 0, nullptr, nullptr }), peripheral({ nullptr, nullptr, 0, nullptr, nullptr }),
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

	music.titleText = addGameObject();
	for (int i = 0; i < 5; ++i) {
		controls[music.titleText].push_back({ to_string(25 * i), [i]() {
			Mix_VolumeMusic(MIX_MAX_VOLUME * i / 4);
		} 
		});
	}

	sfx.titleText = addGameObject();
	for (int i = 0; i < 5; ++i) {
		controls[sfx.titleText].push_back({ to_string(25 * i), [i]() {
			Mix_MasterVolume(MIX_MAX_VOLUME * i / 4);
		} 
		});
	}

	fullWindow.titleText = addGameObject();
	controls[fullWindow.titleText].push_back({ "NO", []() {
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, 0);
		}
	} 
	});
	controls[fullWindow.titleText].push_back({ "SI", []() {
		SDL_Window* window_ = sdlutils().window();
		auto flags = SDL_GetWindowFlags(window_);
		if (!(flags & SDL_WINDOW_FULLSCREEN)) {
			SDL_SetWindowSize(window_, WIN_WIDTH, WIN_HEIGHT);
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
		}
	} 
	});

	peripheral.titleText = addGameObject();
	controls[peripheral.titleText].push_back({ "TECLADO + RATON", [&]() { 
		hideGamepadConnection(); 
		gmCtrl().changeToKeyboard(); 
	} 
	});
	controls[peripheral.titleText].push_back({ "MANDO", [&]() { 
		if (ih().isControllerConnected()) { gmCtrl().changeToGamepad(); }
		else {
			// Si el mando no esta conectado pero esta seleccionado el modo mando, 
			// aparece el texto de conectar el mando y se mantiene a la espera de
			// la conexion del mando desde el OptionsUpdateComponent del peripheral
			showGamepadConnection();

			OptionsUpdateComponent* oUC = peripheral.titleText->getComponent<OptionsUpdateComponent>();
			if (oUC != nullptr) oUC->setPeripheral(true);
		}
	} 
	});
}


// Crea un conjunto de control con titulo y flechas
void OptionsMenuScene::createControl(string title, control& control, OptionId optionId, SDL_Rect controlRect) {

	// Anade el titulo
	control.titleText->addComponent<Transform>(Vector2D(controlRect.x, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.titleText->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), title);
	control.titleText->addComponent<OptionsUpdateComponent>(optionId);

	control.leftArrowButton = createLeftArrow([&, optionId]() { leftOption(control, optionId, controlRect); }, controlRect);
	control.rightArrowButton = createRightArrow([&, optionId]() { rightOption(control, optionId, controlRect); }, controlRect);

	// Se llama a su callback
	controls[control.titleText][control.currentOption].second();

	// Muestra la opcion inicial
	showOption(control, optionId, getOptionRect(controlRect));
}

// Cambia a la opcion de la izquierda y ejecuta su callback
void OptionsMenuScene::leftOption(control control, OptionId optionId, SDL_Rect controlRect) {
	if (!(control.currentOption == 0 && (optionId == _option_MUSIC || optionId == _option_SFX))) {
		--control.currentOption;

		// Si se trataba de la primera opcion, se coloca la ultima opcion
		if (control.currentOption < 0) control.currentOption = controls[control.titleText].size() - 1;
		// Se llama a su callback
		controls[control.titleText][control.currentOption].second();

		showOption(control, optionId, controlRect);
	}
}

// Cambia a la opcion de la derecha y ejecuta su callback
void OptionsMenuScene::rightOption(control control, OptionId optionId, SDL_Rect controlRect) {
	if (!(control.currentOption == 4 && (optionId == _option_MUSIC || optionId == _option_SFX))) {
		++control.currentOption;

		// Si se trataba de la ultima opcion, se coloca la primera
		if (control.currentOption > controls[control.titleText].size() - 1) control.currentOption = 0;
		// Se llama a su callback
		controls[control.titleText][control.currentOption].second();

		showOption(control, optionId, controlRect);
	}
}

// Muestra una opcion de entre las que tenga el objeto
void OptionsMenuScene::showOption(control control, OptionId optionId, SDL_Rect controlRect) {

	// Anade el texto de la opcion
	string optionString = controls[control.titleText][control.currentOption].first;
	if (control.currentOptionText == nullptr) control.currentOptionText = addGameObject();
	control.currentOptionText->addComponent<Transform>(Vector2D(controlRect.x + controlRect.w / 2 - 10 * optionString.size() / 2, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.currentOptionText->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), optionString);
	
	switch (optionId) {
	case _option_MUSIC: music.currentOption = control.currentOption; break;
	case _option_SFX:sfx.currentOption = control.currentOption; break;
	case _option_FULLWINDOW:fullWindow.currentOption = control.currentOption; break;
	case _option_PERIPHERAL: peripheral.currentOption = control.currentOption; break;
	}

	// Reescribe sus callbacks
	if (control.leftArrowButton != nullptr) {
		control.leftArrowButton->setCallBack([&, control, controlRect, optionId]() { leftOption(control, optionId, controlRect); });
	}
	if (control.rightArrowButton != nullptr) {
		control.rightArrowButton->setCallBack([&, control, controlRect, optionId]() { rightOption(control, optionId, controlRect); });
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
	music.currentOption = oD().getMusic();
	sfx.currentOption = oD().getSFX();
	fullWindow.currentOption = oD().getFullWindow();
	peripheral.currentOption = oD().getPeripheral();
}

// Guarda las opciones en el json
void OptionsMenuScene::saveOptions() {
	oD().setMusic(music.currentOption);
	oD().setSFX(sfx.currentOption);
	oD().setFullWindow(fullWindow.currentOption);
	if (ih().isControllerConnected()) oD().setPeripheral(peripheral.currentOption);
	else oD().setPeripheral(0);
}