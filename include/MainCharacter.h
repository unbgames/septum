#pragma once
#include "Component.h"

class MainCharacter : public Component {

  public:
    MainCharacter (GameObject& associated);
    ~MainCharacter ();

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

    static MainCharacter* mainCharacter;
};
