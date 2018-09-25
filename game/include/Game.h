#pragma once

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include <string>
#include <memory>
#include <stack>

using std::string;
using std::stack;
using std::unique_ptr;

/**
 * Game engine class is responsible for resource initialization, main game loop
 * and resource deallocation. It is a Singleton class.
 */
class Game {
	public:

		~Game ();

		/**
		 * Main game loop
		 */
		void Run ();

		/**
		 * Returns active SDL Renderer
		 * @return SDL Renderer
		 */
		SDL_Renderer* GetRenderer () const;

		/**
		 * Returns game state
		 * @return game state
		 */
		State& GetCurrentState () const;

		/**
		 * Returns Singleton instance of Game
		 * @return game instance
		 */
		static Game& GetInstance ();

		void Push (State* state);

		/**
		 * Returns frame time interval in seconds
		 * @return delta time
		 */
		float GetDeltaTime () const;

		int GetWidth () const;

		int GetHeight () const;
	private:
		/**
		 * Game private constructor
		 * @param title  Window title
		 * @param width  Window width
		 * @param height Window height
		 */
		Game (string title, int width, int height);
		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* storedState;
		stack<unique_ptr<State>> stateStack;
		int frameStart;
		float dt;
		int width;
		int height;
		/**
		 * Calculates frame time interval
		 */
		void CalculateDeltaTime ();
};
