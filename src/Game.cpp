#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <stdexcept>
#include "Game.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
	// Follows Singleton design patter
	if (instance == nullptr) {
		instance = new Game("Eduardo Sousa - 13/0108405", 1024, 600);
	}
	return *instance;
}
Game::Game(const char* title, int width, int height) {
	// Initializes SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes SDL_image
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
		throw std::runtime_error(SDL_GetError());
	}
	if(Mix_Init(MIX_INIT_OGG) == 0){
		throw std::runtime_error(SDL_GetError());
	}
	Mix_AllocateChannels(32);

	// Initializes window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr){
		throw std::runtime_error(SDL_GetError());
	}

	// Initializes renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr){
		throw std::runtime_error(SDL_GetError());
	}

//	Initializes state
	state = nullptr;
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

void Game::Run(){
	while(!state->QuitRequested()){
		state->Update(SDL_QuitRequested());
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}
