#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

using std::weak_ptr;
using std::vector;
using std::shared_ptr;

class State {
	public:
		State ();
		virtual ~State ();

		/**
		 * Loads game assets
		 */
		virtual void LoadAssets () = 0;
		/**
		 * Updates game state
		 * @param dt time interval since last update
		 */
		virtual void Update (float dt) = 0;
		/**
		 * Renders state on window
		 */
		virtual void Render () = 0;

		virtual void Start () = 0;
		virtual void Pause () = 0;
		virtual void Resume () = 0;

		virtual weak_ptr<GameObject> AddObject (GameObject*);
		virtual weak_ptr<GameObject> GetObjectPtr (GameObject*);

		bool PopRequested () const;
		/**
		 * Returns whether there was a close command to the game
		 * @return if the close command was issued by the game
		 */
		bool QuitRequested () const;

	protected:

		/**
		 * Starts all objects of the StageState
		 */
		void StartArray ();
		/**
		 * Updates all objects of the StageState
		 * @param dt time interval since last update
		 */
		virtual void UpdateArray (float dt);
		/**
		 * Renders all objects of the StageState
		 */
		virtual void RenderArray ();

		bool popRequested = false;
		bool quitRequested = false;
		bool started = false;

		vector<shared_ptr<GameObject>> objectArray;

	private:
};
