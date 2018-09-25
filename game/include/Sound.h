#pragma once
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include "Component.h"
#include <memory>

using std::string;
using std::shared_ptr;

class Sound: public Component {
	public:
		Sound (GameObject& associated);
		/**
		 * Sound constructor
		 * @param associated GameObjected that encapsulates the sound
		 * @param file image file
		 */
		Sound (GameObject& associated, string file);
		~Sound ();
		/**
		 * Plays the sound
		 * @param times times to be looped
		 */
		void Play (int times = 1);
		/**
		 * Stops the sound playing
		 */
		void Stop ();
		/**
		 * Opens a sound file
		 * @param file audio file
		 */
		void Open (string file);
		/**
		 * Returns if the file is open
		 * @retval true there is an open file
		 * @retval false there is no file
		 */
		bool IsOpen () const;

		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @retval true the passed type is Sound
		 * @retval false the passed type is not Sound
		 */
		bool Is (string type) const;

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);

		/**
		 *
		 */
		void Render ();

		int GetChannel () const;

	private:
		shared_ptr<Mix_Chunk> chunk;
		int channel = -1;
};
