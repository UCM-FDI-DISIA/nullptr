#include "SDLApplication.h"

// Constructor
SDLApplication::SDLApplication() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Timeless Deck - Es Tiempo", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw SDL_SetError("Could not load window.");

	ifstream file(TEXTURES_FILE);
	if (!file) {
		file.close();
		//throw FileNotFoundError(TEXTURES_FILE);
		throw "Could not find file: " + TEXTURES_FILE;
	}
	try {
		while (!file.eof()) {
			string key, path; uint hframes, vframes;
			file >> key >> path >> vframes >> hframes;
			texturesMap[key] = new Texture(renderer, path, hframes, vframes);
		}
		file.close();
	}
	catch (string error) {
		file.close();
		//throw FileFormatError("Invalid textures file. " + error);
		throw "File format error. Invalid textures file. " + error;
	}

	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new GameState(this));
	exit = false;
}

// Destructor
SDLApplication::~SDLApplication() {
	for (auto it : texturesMap) {
		delete(it.second);
	}
	delete(gameStateMachine);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Executes the game
void SDLApplication::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit) {
		update();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= DELAY_TIME) {
			render();
			startTime = SDL_GetTicks();
		}
		handleEvents();
	}
	gameStateMachine->clearStates();
}

// Draws the game on screen
void SDLApplication::render() const {
	SDL_RenderClear(renderer);
	gameStateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}

// Updates all the game entities
void SDLApplication::update() {
	gameStateMachine->currentState()->update();
	gameStateMachine->clearStatesToErase();
}

// Updates the game depending on the current event 
void SDLApplication::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		gameStateMachine->currentState()->handleEvent(event);
	}
}

// Returns needed Texture
Texture* SDLApplication::getTexture(TextureName texture) const { return texturesMap.at(texture); }


// Starts game
void SDLApplication::playGame(SDLApplication* _game) {  }

// Pauses the game
void SDLApplication::pauseGame(SDLApplication* _game) { /*_game->gameStateMachine->pushState(new PauseMenuState(_game));*/ }

// Resumes the game
void SDLApplication::resumeGame(SDLApplication* _game) { SDLApplication::popGameState(_game); }

// Pops the top state
void SDLApplication::popGameState(SDLApplication* _game) { _game->gameStateMachine->popState(); }

// Quits the game
void SDLApplication::quitGame(SDLApplication* _game) { _game->exit = true; }