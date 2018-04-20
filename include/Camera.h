#pragma once
#include "Vec2.h"
#include "GameObject.h"
class Camera {
	public:
		/**
		 * Set the camera to follow an object
		 * @param newFocus Object to follow
		 */
		static void Follow (GameObject* newFocus);

		/**
		 * Unfollow object
		 */
		static void Unfollow ();

		/**
		 * Updates camera state
		 * @param dt
		 */
		static void Update (float dt);
		
		static Vec2 pos;
		static Vec2 speed;

	private:
		static GameObject* focus;
};
