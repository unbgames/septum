#pragma once
#include "Component.h"
#include "Damageable.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"

class Humano : public Damageable {

  public:
    Humano (GameObject& associated);
    ~Humano ();
    enum stateType{IDLE,WALK,JUMP,BLOCK,CROUCH};
    stateType characterState;
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
		 * @retval true the passed type is MainCharacter
		 * @retval false the passed type is not MainCharacter
		 */
		bool Is (string type) const;
		void ChangeState(stateType state);

    //static MainCharacter* mainCharacter;

  private:
  	Collider* collisionbox;
    Sprite* spr;
    bool stateChanged = false;
};
