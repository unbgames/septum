#pragma once
#include <string>

using std::string;

class GameObject;
/**
 * Component that adds a behavior to a GameObject
 */
class Component {
	public:
		Component (GameObject& associated);
		virtual ~Component ();

		/**
		 * Updates component state
		 * @param dt
		 */
		void virtual Update (float dt) = 0;

		/**
		 * Renders the component
		 */
		void virtual Render () = 0;

		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @return whether the type matches or not
		 */
		bool virtual Is (string type) const = 0;
		/**
		 * Sets the component up
		 */
		void virtual Start ();

		void virtual NotifyCollision (GameObject& other);

	protected:
		GameObject& associated;
};
