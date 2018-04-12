#pragma once
#include "Component.h"
#include "GameObject.h"

class Face: public Component {
	public:
		Face (GameObject& associated);

		/**
		 * Damages the face
		 * @param damage amount of hp removed
		 */
		void Damage (int damage);

		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @retval true the passed type is Face
		 * @retval false the passed type is not Face
		 */
		bool Is (string type) const;

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);

		/**
		 * Renders the face
		 */
		void Render ();
	private:
		int hitpoints;
};
