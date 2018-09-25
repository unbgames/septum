#pragma once
#include "Component.h"
#include "Sound.h"
#include <unordered_map>
#include <memory>

using std::string;
using std::unordered_map;
using std::shared_ptr;
class SoundCollection: public Component {
	public:
		SoundCollection (GameObject& associated);
		~SoundCollection ();
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
		 * @retval true the passed type is Sound
		 * @retval false the passed type is not Sound
		 */
		bool Is (string type) const;

    shared_ptr<Sound> GetSound(string identifier);
    bool AddSound (string identifier, Sound* sound);
		unordered_map<string, shared_ptr<Sound>> sounds;
};
