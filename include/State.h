#pragma once
#include "Sprite.h"
#include "Music.h"

/**
 * Class of game current state
 */
class State {
	public:
		State ();
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
	private:
		Sprite bg;
		Music music;
		bool quitRequested;
};
