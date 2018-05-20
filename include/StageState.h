#pragma once
#include "GameObject.h"
#include "Music.h"
#include "State.h"


/**
 * Class of game current state
 */
class StageState: public State {
	public:
		StageState ();
		~StageState ();

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
		Music music;
		GameObject map;
		GameObject bg;
};
