#pragma once
#include "Vec2.h"
#include "Rect.h"
class Camera {
	public:
		/**
		 * Set the camera to follow an object
		 * @param newFocus Object to follow
		 */
		static void Follow (Rect* newFocus);

		/**
		 * Unfollow object
		 */
		static void Unfollow ();

		/**
		 * Updates camera state
		 * @param dt
		 */
		static void Update (float dt);
		static bool IsFollowing();
		static Vec2 pos;
		static Vec2 speed;

	private:
		static Rect* focus;
};
