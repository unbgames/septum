#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include <string>

using std::string;

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
		State& GetState () const;

		/**
		 * Returns Singleton instance of Game
		 * @return game instance
		 */
		static Game& GetInstance ();

		/**
		 * Returns frame time interval in seconds
		 * @return delta time
		 */
		float GetDeltaTime () const;

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
		State* state;
		int frameStart;
		float dt;
		/**
		 * Calculates frame time interval
		 */
		void CalculateDeltaTime ();
};
