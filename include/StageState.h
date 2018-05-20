#pragma once
#include "GameObject.h"
#include "Music.h"
#include <vector>
#include "State.h"
#include <memory>

using std::vector;
using std::shared_ptr;
using std::weak_ptr;

/**
 * Class of game current state
 */
class StageState: public State {
	public:
		StageState ();
		~StageState ();
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
		 * Starts all objects of the StageState
		 */
		void Start ();

		/**
		 * Adds an object to the StageState
		 * @param go object to be added
		 * @return weak pointer reference to the game object
		 */
		weak_ptr<GameObject> AddObject (GameObject* go);

		/**
		 * Returns a weak pointer to the passed GameObject
		 * @param go GameObject
		 * @return weak pointer
		 */
		weak_ptr<GameObject> GetObjectPtr (GameObject* go);
	private:
		Music music;
		GameObject map;
		GameObject bg;
		bool quitRequested;
		bool started;
		vector<shared_ptr<GameObject>> objectArray;
};
