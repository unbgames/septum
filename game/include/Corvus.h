#pragma once
#include "Component.h"
#include "Colliders.h"
#include "Damageable.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"
#include "Timer.h"
#include "SoundCollection.h"
class Corvus : public Damageable {

  public:
    Corvus (GameObject& associated);
    ~Corvus ();
    enum stateType{IDLE,WALK,ATTACK,DEAD};
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
    void StateLogic();
    Vec2 GetCharacterPosition();
    //static MainCharacter* mainCharacter;

  private:
  	Colliders* colliders;
    SoundCollection* effects;
    Sprite* spr;
    bool stateChanged = false;
    Vec2 speed = {0, 0};
    Timer animationTimer;
    Timer stateTimer;
    bool attacking = false;
    bool playerHit = false;
};
