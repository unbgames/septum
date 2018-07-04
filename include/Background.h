#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Sprite.h"

using std::unique_ptr;
using std::string;
using std::vector;

class Background: public Component {
	public:
		Background (GameObject& associated, float parallax = 0);

		~Background ();
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
		 * Checks if the Component is from the type Background
		 * @param type type to be checked
		 * @return whether the type matches or not
		 */
		bool Is (string type) const;

		void SetParallax (float plx);
		float GetParallax ();

		void AddLayer (Sprite* spr);

	private:
		vector<unique_ptr<Sprite>> layers;
		float parallax;
};
