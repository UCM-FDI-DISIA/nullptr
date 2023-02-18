#include "SDLApplication.h"

// Constructor
SDLApplication::SDLApplication() {

	SDLUtils::init("Timeless Deck - Es tiempo", WIN_WIDTH, WIN_HEIGHT, "../Game/src/data/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();

	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new MainMenuScene(this));
	exit = false;
}

// Destructor
SDLApplication::~SDLApplication() {
	delete(gameStateMachine);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Executes the game
// Ejecuta el juego
void SDLApplication::run() {
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

// Draws the game on screen
// Dibuja el juego en pantalla
void SDLApplication::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Updates all the game entities
// Actualiza todas las entidades del juego
void SDLApplication::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Updates the game depending on the current event
// Actualiza el juego en función al evento actual
void SDLApplication::handleInput() {
	gameStateMachine->currentState()->handleInput();
}

// Returns needed Texture
// Devuelve la Texture pedida
Texture* SDLApplication::getTexture(TextureName texture) const { return &SDLUtils::instance()->images().at(texture); /*return texturesMap.at(texture);*/ }

//Launches a new GameScene
//Lanza una nueva escena del juego
void SDLApplication::beginScene(SDLApplication* _game, GameState* newScene) {
	_game->gameStateMachine->changeState(newScene);
}

// Pauses the game
// Pausa el juego
void SDLApplication::pauseGame(SDLApplication* _game) { /*_game->gameStateMachine->pushState(new PauseMenuState(_game));*/ }

// Resumes the game
// Reanuda el juego
void SDLApplication::resumeGame(SDLApplication* _game) { SDLApplication::popGameState(_game); }

// Pops the top state
// Elimina el estado en la cima de la pila
void SDLApplication::popGameState(SDLApplication* _game) { _game->gameStateMachine->popState(); }

// Quits the game
// Cierra el juego
void SDLApplication::quitGame(SDLApplication* _game) { _game->exit = true; }