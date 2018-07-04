#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"
class Collider {
	public:
		Collider (GameObject& associated, Vec2 scale = { 1, 1 }, Vec2 offset = {
				0, 0 }, bool enabled = true);
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

		void SetScale (Vec2 scale);

		void SetOffset (Vec2 offset);

		void Enable();
		void Disable();
		bool IsEnabled();

	private:
		GameObject& associated;
		Vec2 scale;
		Vec2 offset;
		bool enabled;
};
