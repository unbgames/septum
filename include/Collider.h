#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Rect.h"
class Collider: public Component {
	public:
		Collider (GameObject& associated, Vec2 scale = { 1, 1 }, Vec2 offset = {
				0, 0 });
		Rect box;

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
		 * @retval true the passed type is Collider
		 * @retval false the passed type is not Collider
		 */
		bool Is (string type) const;

		void SetScale (Vec2 scale);

		void SetOffset (Vec2 offset);

	private:
		Vec2 scale;
		Vec2 offset;
};
