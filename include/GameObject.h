#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include "Rect.h"

using std::vector;
using std::string;

/**
 * The GameObject contains a vector of components describing its behavior
 */
class GameObject {
	public:
		GameObject();
		~GameObject();

		/**
		 * Update all GameObject components
		 * @param dt
		 */
		void Update(float dt);

		/**
		 * Renders all GameObject components
		 */
		void Render();

		/**
		 * Deletion state of GameObject
		 * @retval true GameObject is deleted
		 * @retval false GameObject is not deleted
		 */
		bool IsDead ();

		/**
		 * Deletes GameObject
		 */
		void RequestDelete();

		/**
		 * Adds component to GameObject
		 * @param cpt component to be added
		 */
		void AddComponent(Component* cpt);

		/**
		 * Removes component from GameObject
		 * @param cpt component to be removed
		 */
		void RemoveComponent(Component* cpt);

		/**
		 * Gets component from GameObject
		 * @param type component type
		 * @return requested component
		 */
		Component* GetComponent (string type);

		/**
		 * GameObject position and dimension on window
		 */
		Rect box;

	private:
		vector<Component*> components;
		bool isDead;
};
