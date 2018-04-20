#pragma once
#include "Component.h"
class CameraFollower: public Component {
	public:
		CameraFollower (GameObject& go);

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
		 * Checks if the Component is a CameraFollower
		 * @param type type to be checked
		 * @return whether the type matches or not
		 */
		bool Is (string type) const;
};
