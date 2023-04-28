#include "OptionsMenuScene.h"
#include "../core/SDLApplication.h"
#include <cstdarg>

// Constructora
OptionsMenuScene::OptionsMenuScene() : volume({ nullptr, { nullptr, 0} }), fullWindow({ nullptr, { nullptr, 0} }), peripheral({ nullptr, { nullptr, 0} }),
volumeLeftButton(nullptr), volumeRightButton(nullptr), fullWindowLeftButton(nullptr), fullWindowRightButton(nullptr), peripheralLeftButton(nullptr), peripheralRightButton(nullptr) {
	
	addBackground();

	// Boton de salida
	AnimatorInfo aI = AnimatorInfo(EXIT);
	addGameObject<Button>([]() { SDLApplication::popGameState(); }, Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH - 50, WIN_HEIGHT - MM_BUTTON_HEIGHT - 50), aI)->setAsDefaultButton();
	

	createControl("Volumen", volume, volumeRect, volumeLeftButton, volumeRightButton, 3, "Bajo", "Medio", "Alto");
	createControl("Pantalla Completa", fullWindow, fullWindowRect, fullWindowLeftButton, fullWindowRightButton, 2, "No", "Si");
	createControl("Control", peripheral, peripheralRect, peripheralLeftButton, peripheralRightButton, 2, "Teclado", "Mando");

	/*aI.key = OPTIONS;
	addGameObject<Button>([]() { sdlutils().toggleFullScreen(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 200), aI);
	aI.key = OPTIONS;
	addGameObject<Button>([]() { gmCtrl().changeControl(); }, Vector2D(WIN_WIDTH / 2 - 79, (WIN_HEIGHT / 4) + 350), aI);*/
}

// Destructora
OptionsMenuScene::~OptionsMenuScene() {}

// Anade el fondo
void OptionsMenuScene::addBackground() {
	// Imagen de fondo
	background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));
}

// Crea un conjunto de control con titulo y flechas
void OptionsMenuScene::createControl(string title, pair<GameObject*, pair<GameObject*, int>> control, SDL_Rect controlRect, 
	Button* leftButton, Button* rightButton, int numStrings, ...) {

	// Anade el titulo
	control.first = addGameObject();
	control.first->addComponent<Transform>(Vector2D(controlRect.x, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.first->addComponent<TextComponent>(SDLApplication::getFont(USED_FONT), title);

	// Anade las opciones con sus respectivos callbacks
	va_list args;
	va_start(args, numStrings);
	for (int i = 0; i < numStrings; ++i) {
		const char* str = va_arg(args, const char*);
		std::string s(str);
		controls[control.first][i] = { s, []() { cout << "HOLAA";  } };
	}
	va_end(args);

	SDL_Rect optionsRect = { controlRect.x + controlRect.w + 120, controlRect.y, 330, MM_BUTTON_HEIGHT };

	AnimatorInfo aI = AnimatorInfo("LeftArrow", 64, 44, 32, 22, 1, 3);
	leftButton = addGameObject<Button>([&, control, leftButton, rightButton, controlRect]() { leftOption(control, leftButton, rightButton, controlRect); }, Vector2D(optionsRect.x - 70, optionsRect.y), aI);
	aI = AnimatorInfo("RightArrow", 64, 44, 32, 22, 1, 3);
	rightButton = addGameObject<Button>([&, control, leftButton, rightButton, controlRect]() { rightOption(control, leftButton, rightButton, controlRect); }, Vector2D(optionsRect.x + optionsRect.w + 70, optionsRect.y), aI);

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
void OptionsMenuScene::showOption(pair<GameObject*, pair<GameObject*, int>> control, Button* leftButton, Button* rightButton, SDL_Rect controlRect) {

	string optionString = controls[control.first][control.second.second].first;
	if (control.second.first == nullptr) control.second.first = addGameObject();
	control.second.first->addComponent<Transform>(Vector2D(controlRect.x + controlRect.w / 2 - optionString.size() / 2, controlRect.y), Vector2D(), controlRect.w, controlRect.h);
	control.second.first->addComponent<TextComponent>(SDLApplication::getFont(USED_FONT), optionString);
	
	// Establece las flechas
	if (leftButton != nullptr) {
		leftButton->setCallBack([&, control, leftButton, rightButton, controlRect]() { leftOption(control, leftButton, rightButton, controlRect); });
	}
	if (rightButton != nullptr) {
		rightButton->setCallBack([&, control, leftButton, rightButton, controlRect]() { rightOption(control, leftButton, rightButton, controlRect); });
	}
}