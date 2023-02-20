#include "SDLApplication.h"

// Constructora
SDLApplication::SDLApplication() {

	// Creacion de la ventana
	SDLUtils::init("Timeless Deck - Es tiempo", WIN_WIDTH, WIN_HEIGHT, "../Game/src/data/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();
	utils->toggleFullScreen();

	// Maquina de estados
	gameStateMachine = new GameStateMachine();
	exit = false;
}

// Destructora
SDLApplication::~SDLApplication() {
	delete(gameStateMachine);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Ejecuta el juego
void SDLApplication::run() {
	gameStateMachine->pushState(new MainMenuScene());

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) {
		InputHandler::instance()->refresh();
		frameTime = SDL_GetTicks() - startTime;
		update();
		if (frameTime >= DELAY_TIME) {
			startTime = SDL_GetTicks();
			render();
		}
		handleInput();
	}
	gameStateMachine->clearStates();
}

// Dibuja el juego en pantalla
void SDLApplication::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Actualiza todas las entidades del juego
void SDLApplication::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Actualiza el juego en función al evento actual
void SDLApplication::handleInput() {
	gameStateMachine->currentState()->handleInput();
}

// Devuelve la Texture pedida
Texture* SDLApplication::getTexture(TextureName texture) { return &SDLUtils::instance()->images().at(texture); }

//Lanza una nueva escena del juego
void SDLApplication::beginScene(GameState* newScene) {
	SDLApplication::instance()->gameStateMachine->changeState(newScene);
}

// Pausa el juego
void SDLApplication::pauseGame() { /*_game->gameStateMachine->pushState(new PauseMenuState(_game));*/ }

// Reanuda el juego
void SDLApplication::resumeGame() { SDLApplication::popGameState(); }

// Elimina el estado en la cima de la pila
void SDLApplication::popGameState() { SDLApplication::instance()->gameStateMachine->popState(); }

// Cierra el juego
void SDLApplication::quitGame() { SDLApplication::instance()->exit = true; }