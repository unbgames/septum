#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"
class Collider {
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

		void SetScale (Vec2 scale);

		void SetOffset (Vec2 offset);

	private:
		GameObject& associated;
		Vec2 scale;
		Vec2 offset;
};
