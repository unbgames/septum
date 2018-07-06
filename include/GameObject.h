#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "Rect.h"

using std::vector;
using std::unique_ptr;
using std::string;

/**
 * The GameObject contains a vector of components describing its behavior
 */
class GameObject {
	public:
		GameObject();
		~GameObject();

		/**
		 * Starts all components of the GameObject
		 */
		void Start ();

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
		bool IsDead () const;

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
		Component* GetComponent (string type) const;

		void NotifyCollision (GameObject& other, string idCollider, string idOtherCollider);

		void NotifyAnimationEnd ();


		/**
		 * GameObject position and dimension on window
		 */
		Rect box;

		double angleDeg = 0;
		bool flipHorizontal = false;
		void Flip (bool value);
		void ChangePositionOffset(Vec2 offset, float flipOffset = 0);
		Vec2 positionOffset = {0, 0};
		float flipOffset = 0;

	private:
		vector<unique_ptr<Component>> components;
		bool isDead;
		bool started;
};
