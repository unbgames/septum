#pragma once
#include "Component.h"
#include <memory>
#include "Vec2.h"

using std::weak_ptr;
class PenguinBody: public Component {
	public:
		PenguinBody (GameObject& associated);
		~PenguinBody ();

		/**
		 * Sets the component up
		 */
		void Start ();
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
		 * @retval true the passed type is PenguinBody
		 * @retval false the passed type is not PenguinBody
		 */
		bool Is (string type) const;
		
		void NotifyCollision (GameObject& other);

		Vec2 GetCenterPosition () const;


		static PenguinBody* player;

	private:

		weak_ptr<GameObject> pcannon;
		Vec2 speed;
		float linearSpeed;
		float angle;
		int hp;
};
