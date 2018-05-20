#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <stdexcept>
#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

using std::string;

Game* Game::instance = nullptr;

Game& Game::GetInstance () {
	if (instance == nullptr) {
		new Game("Eduardo Sousa - 13/0108405", 1024, 600);
	}
	return *instance;
}
Game::Game (string title, int width, int height) :
		width(width), height(height) {
	if (instance != nullptr) {
		throw std::runtime_error("Game already instantiated");
	}
	else {
		instance = this;
	}

	srand(time(NULL));

	// Initializes SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		throw std::runtime_error(SDL_GetError());
	}

	dt = 0;

	frameStart = 0;

	if (TTF_Init() != 0) {
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
	storedState = nullptr;
}

Game::~Game () {
	if (storedState) {
		delete (storedState);
	}
	while (!stateStack.empty()) {
		stateStack.pop();
	}

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	Resources::ClearFonts();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	TTF_Quit();

	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer () const {
	return renderer;
}

State& Game::GetCurrentState () const {
	return *stateStack.top();
}

void Game::CalculateDeltaTime () {
	int newFrame = SDL_GetTicks();
	dt = (newFrame - frameStart) / 1000.0;

	frameStart = newFrame;
}

float Game::GetDeltaTime () const {
	return dt;
}

void Game::Run () {
	if (storedState) {
		stateStack.emplace(storedState);
		stateStack.top()->Start();
		storedState = nullptr;
		while (!stateStack.top()->QuitRequested() && !stateStack.empty()) {
			if (stateStack.top()->PopRequested()) {
				stateStack.pop();
				Resources::ClearImages();
				Resources::ClearMusics();
				Resources::ClearSounds();
				Resources::ClearFonts();
				if (!stateStack.empty()) {
					stateStack.top()->Resume();
				}
			}
			if (storedState) {
				if (!stateStack.empty()) {
					stateStack.top()->Pause();
				}
				stateStack.emplace(storedState);
				stateStack.top()->Start();
				storedState = nullptr;
			}
			CalculateDeltaTime();
			InputManager::GetInstance().Update();
			stateStack.top()->Update(dt);
			stateStack.top()->Render();
			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
	}
}

int Game::GetHeight () const {
	return height;
}

int Game::GetWidth () const {
	return width;
}

void Game::Push (State* state) {
	storedState = state;
}
