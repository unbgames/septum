#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include <string>
#include "SDL_include.h"
#include <unordered_map>

using std::string;
using std::unordered_map;

class Resources {
	public:
		/**
		 * Gets an image resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened texture
		 */
		static SDL_Texture* GetImage (string file);

		/**
		 * Dumps the entire image table
		 */
		static void ClearImages ();

		/**
		 * Gets a music resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened music
		 */
		static Mix_Music* GetMusic (string file);
		/**
		 * Dumps the entire musics table
		 */
		static void ClearMusics ();
		/**
		 * Gets a sound resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened sound
		 */
		static Mix_Chunk* GetSound (string file);
		/**
		 * Dumps the entire sounds table
		 */
		static void ClearSounds ();

	private:
		static unordered_map<string, SDL_Texture*> imageTable;
		static unordered_map<string, Mix_Music*> musicTable;
		static unordered_map<string, Mix_Chunk*> soundTable;
};
