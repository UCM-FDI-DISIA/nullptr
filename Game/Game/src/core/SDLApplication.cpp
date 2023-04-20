#include "SDLApplication.h"

// Constructora
SDLApplication::SDLApplication() {
	// Crea las constantes
	Constant::getNumbersFromJSON();

	// Creacion de la ventana
	SDLUtils::init("Timeless Deck - Es tiempo", Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"), "../Game/src/data/game.resources.json");
	utils = SDLUtils::instance();
	window = utils->window();
	renderer = utils->renderer();
	//utils->toggleFullScreen();
	utils->hideCursor();
	utils->focusMouseOnWindow();

	// Maquina de estados
	gameStateMachine = new GameStateMachine();
	exit = false;
}

// Destructora
SDLApplication::~SDLApplication() {
	delete(gameStateMachine);
}

// Ejecuta el juego
void SDLApplication::run() {
	gameStateMachine->pushState(new MainMenuScene());



	uint32_t frameTime; double debugCounter;
	startTime = SDL_GetTicks();
	timeOffset = startTime;
	debugCounter = 0;
	
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	

	

	while (!exit) {
		InputHandler::instance()->refresh();
		
		frameTime = SDL_GetTicks() - startTime;
		
		update();
		
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		debugCounter += deltaTime;

		if (frameTime >= DELAY_TIME) {
			
			startTime = SDL_GetTicks();
			
			render();
		}
		
		// Descomentar para analizar el deltaTime
		// std::cout << deltaTime << " " << SDL_GetTicks() << " " <<  debugCounter << " " << SDL_GetTicks() - debugCounter << " " << timeOffset << std::endl;
		
		handleInput();

		if (ih().closeWindowEvent()) {
			exit = true;
		}
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

// Actualiza el juego en funci�n al evento actual
void SDLApplication::handleInput() {
	gameStateMachine->currentState()->handleInput();
}

// Devuelve la Texture pedida
Texture* SDLApplication::getTexture(TextureName texture) { return &sdlutils().images().at(texture); }

// Devuelve el Font pedido
Font* SDLApplication::getFont(string fontName) { return &sdlutils().fonts().at(fontName); }

// Devuelve la Reliquia pedida
Relic* SDLApplication::getRelic(TextureName texture) { return &sdlutils().relics().at(texture); }

// Devuelve un numero entero random
int SDLApplication::getRandInt(int min, int max) { return sdlutils().rand().nextInt(min, max); }

// Pausa el juego
void SDLApplication::pauseGame() { SDLApplication::instance()->gameStateMachine->pushState(new PauseMenuScene()); }

// Reanuda el juego
void SDLApplication::resumeGame() { SDLApplication::popGameState(); }

// Elimina el estado en la cima de la pila
void SDLApplication::popGameState() { SDLApplication::instance()->gameStateMachine->popState(); }

//
void SDLApplication::returnToMapScene() {
	popGameState();
	MapScene* ms = dynamic_cast<MapScene*>(SDLApplication::instance()->gameStateMachine->currentState());
	assert(ms != nullptr);
	ms->moveCamera();
}

// Cierra el juego
void SDLApplication::quitGame() { SDLApplication::instance()->exit = true; }