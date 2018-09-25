#pragma once
#include "Component.h"

class Damageable : public Component {

  public:
    Damageable (GameObject& associated, float hp = 0);
    virtual ~Damageable ();

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

    float GetHP () const;
    void SetHP (float hp);

    void virtual OnDamage (float damage, GameObject& source);

    void Damage (float damage, GameObject& source);
  private:
    float hp;
    float damageResistance;
};
