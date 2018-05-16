#pragma once
#include "Component.h"
#include "GameObject.h"
class Bullet: public Component {
	public:
		/**
		 * Fires a projectile in a direction
		 * @param associated associated GameObjecte
		 * @param angle angle of the projectile
		 * @param speed speed of the projectile
		 * @param damage projectile damage
		 * @param maxDistance max distance before deletion
		 * @param sprite file path to the projectile sprite
		 */
		Bullet (GameObject& associated, float angle, float speed, int damage,
				float maxDistance, string sprite, bool targetsPlayer,
				int frameCount = 1,
				float frameTime = 1);
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
		 * @retval true the passed type is Bullet
		 * @retval false the passed type is not Bullet
		 */
		bool Is (string type) const;

		/**
		 * Gets the damage the projectile deals
		 * @return projectile damage
		 */
		int GetDamage () const;

		void NotifyCollision (GameObject& other);

		bool targetsPlayer;

	private:
		Vec2 speed;
		float distanceLeft;
		int damage;
};
