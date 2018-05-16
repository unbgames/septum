#pragma once
#include "Component.h"
#include <memory>
#include "Timer.h"

using std::weak_ptr;

class PenguinCannon: public Component {
	public:
		PenguinCannon (GameObject& associated, weak_ptr<GameObject> pbody);

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);
		/**
		 * Renders the component
		 */
		void Render ();
		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @retval true the passed type is PenguinBody
		 * @retval false the passed type is not PenguinBody
		 */
		bool Is (string type) const;

		/**
		 * Shoots a Bullet
		 */
		void Shoot ();

	private:

		weak_ptr<GameObject> pbody;
		float angle;
		Timer timer;
};
