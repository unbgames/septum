#pragma once
#include "Component.h"
#include "Collider.h"
#include <unordered_map>
#include <memory>

using std::string;
using std::unordered_map;
using std::shared_ptr;
class Colliders: public Component {
	public:
		Colliders (GameObject& associated);
		~Colliders ();
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
		 * @retval true the passed type is Collider
		 * @retval false the passed type is not Collider
		 */
		bool Is (string type) const;

    shared_ptr<Collider> GetCollider(string identifier);
    bool AddCollider (string identifier, Collider* collider);
    void CheckCollision(GameObject& other);
		unordered_map<string, shared_ptr<Collider>> colliders;
};
