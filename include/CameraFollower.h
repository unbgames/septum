#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
class CameraFollower: public Component {
	public:
		CameraFollower (GameObject& go, Vec2 offset = {0, 0});

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

		Vec2 offset;
};
