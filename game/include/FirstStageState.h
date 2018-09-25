#pragma once
#include "State.h"
#include "TileMap.h"
#include "Timer.h"
#include "Music.h"
class FirstStageState: public State {
	public:
	  FirstStageState ();
		~FirstStageState ();

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
		static float tempoRestante;
		static int enemycount;
		static float tempojogado;
	private:
		Music music;
		Timer tempoJOGO;
		GameObject *cronometro;
		//TileMap map;
};
