#pragma once
#include "Component.h"
#include "Damageable.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Colliders.h"
#include <vector>
#include "Sound.h"

class MainCharacter : public Damageable {

  public:
    MainCharacter (GameObject& associated);
    ~MainCharacter ();
    enum stateType{IDLE,WALK,JUMP,BLOCK,CROUCH,ATTACK,JUMP_ATTACK,CROUCH_ATTACK,DEAD,CROUCH_BLOCK, CROUCH_WALK};
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

    void NotifyAnimationEnd();
    void NotifyCollision (GameObject& other, string idCollider, string idOtherCollider);

    void OnDamage (float damage, GameObject& source);

		bool demon;
		float furia;
    static MainCharacter* mainCharacter;
    Vec2 GetCharacterPosition();
  private:
  	GameObject *som;
    void StateLogic ();

    bool attacking;
  	Colliders* colliders;
    Vec2 speed = {0, 0};
    Sprite* spr;
    bool stateChanged = false;
    Timer animationTimer;
};
