#pragma once
#include "State.h"
#include "Timer.h"

class TitleState: public State {
	public:
		TitleState ();
		~TitleState ();

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
		Timer textTimer;
		GameObject playText;
};
