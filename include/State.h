#pragma once
#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::weak_ptr;

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

//		/**
//		 * Adds a Penguin Object in position
//		 * @param mouseX x-coordinate of penguin
//		 * @param mouseY y-coordinate of penguin
//		 */
//		void AddObject (int mouseX, int mouseY);

		void Start ();

		weak_ptr<GameObject> AddObject (GameObject* go);

		weak_ptr<GameObject> GetObjectPtr (GameObject* go);
	private:
		Music music;
		GameObject map;
		bool quitRequested;
		bool started;
		vector<shared_ptr<GameObject>> objectArray;
};
