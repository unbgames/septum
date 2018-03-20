#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <stdexcept>
#include "Game.h"

using std::string;

Game* Game::instance = nullptr;

Game& Game::GetInstance () {
	if (instance == nullptr) {
		new Game("Eduardo Sousa - 13/0108405", 1024, 600);
	}
	return *instance;
}
Game::Game (string title, int width, int height) {
	if (instance != nullptr) {
		throw std::runtime_error("Game already instantiated");
	}
	else {
		instance = this;
	}
	// Initializes SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes SDL_image
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)
			!= (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
	MIX_DEFAULT_CHANNELS, 1024) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	if (Mix_Init(MIX_INIT_OGG) == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	Mix_AllocateChannels(32);

	// Initializes window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

//	Initializes state
	state = new State();
}

Game::~Game () {
	delete(state);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer () const{
	return renderer;
}

void Game::Run () {
	// Waits for quit signal
	while (!state->QuitRequested()) {
		//Renders current State
		state->Update(0);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}