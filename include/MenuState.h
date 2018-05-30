#pragma once
#include "State.h"

class MenuState: public State {
	public:
	 	MenuState ();
		~MenuState ();

		/**
		 * Loads game assets
		 */
		void LoadAssets ();
		/**
		 * Updates game state
		 * @param dt time interval since last update
		 */
		void Update (float dt);
		/**
		 * Renders state on window
		 */
		void Render ();

		void Start ();
		void Pause ();
		void Resume ();

	private:
};
