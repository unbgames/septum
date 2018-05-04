#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include <string>
#include <memory>

using std::string;
using std::weak_ptr;

class Minion: public Component {
	public:
		/**
		 * Creates a Minion to orbit an Alien
		 * @param associated associated gameObject
		 * @param alienCenter weak pointer to alien
		 * @param arcOffsetDeg minion starting angle
		 */
		Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
				float arcOffsetDeg = 0);
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
		 * @retval true the passed type is Minion
		 * @retval false the passed type is not Minion
		 */
		bool Is (string type) const;
		/**
		 * Shoots a Bullet on a target
		 * @param target bullet target
		 */
		void Shoot (Vec2 target);
	private:
		weak_ptr<GameObject> alienCenter;
		float arc;
};
