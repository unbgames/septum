#pragma once
#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

/**
 * Class of game current state
 */
class State {
	public:
		State ();
		~State ();
		/**
		 * Returns whether there was a close command to the game
		 * @return if the close command was issued by the game
		 */
		bool QuitRequested () const;
		/**
		 * Loads game assets
		 */
		void LoadAssets ();
		/**
		 * Updates game state
		 * @param dt
		 */
		void Update (float dt);
		/**
		 * Renders state on window
		 */
		void Render ();
		/**
		 * Deals with user input
		 */
		void Input ();

		/**
		 * Adds a Penguin Object in position
		 * @param mouseX x-coordinate of penguin
		 * @param mouseY y-coordinate of penguin
		 */
		void AddObject (int mouseX, int mouseY);
	private:
		Music music;
		bool quitRequested;
		vector<unique_ptr<GameObject>> objectArray;
};
