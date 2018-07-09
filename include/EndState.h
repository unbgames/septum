#pragma once
#include "State.h"
#include "TileMap.h"
#include "Timer.h"
class EndState: public State {
	public:
	  EndState ();
		~EndState ();

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
		//TileMap map;
};
