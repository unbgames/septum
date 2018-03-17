#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include <string>

using std::string;

class Game {
	public:
		~Game ();
		void Run ();
		SDL_Renderer* GetRenderer ();
		State& GetState ();
		static Game& GetInstance ();

	private:
		Game (string title, int width, int height);

		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;
};

