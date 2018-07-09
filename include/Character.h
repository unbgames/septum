#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Colliders.h"
#include <vector>

class Character : public Component {

  public:
    enum factionType { NEUTRAL, PLAYER, COMPUTER };
    Character (GameObject& associated, factionType faction);
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
		 * @retval true the passed type is Character
		 * @retval false the passed type is not Character
		 */
		bool Is (string type) const;
    factionType faction;
};
