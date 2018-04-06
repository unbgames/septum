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
		bool QuitRequested ();
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
		void Input ();
		void AddObject (int mouseX, int mouseY);
	private:
		GameObject bg;
		Music music;
		bool quitRequested;
		vector<unique_ptr<GameObject>> objectArray;
};
