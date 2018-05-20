#pragma once
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <string>
#include "SDL_include.h"
#include <unordered_map>
#include <memory>

using std::string;
using std::unordered_map;
using std::shared_ptr;

class Resources {
	public:
		/**
		 * Gets an image resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened texture
		 */
		static shared_ptr<SDL_Texture> GetImage (string file);

		/**
		 * Dumps the entire image table
		 */
		static void ClearImages ();

		/**
		 * Gets a music resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened music
		 */
		static shared_ptr<Mix_Music> GetMusic (string file);
		/**
		 * Dumps the entire musics table
		 */
		static void ClearMusics ();
		/**
		 * Gets a sound resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened sound
		 */
		static shared_ptr<Mix_Chunk> GetSound (string file);
		/**
		 * Dumps the entire sounds table
		 */
		static void ClearSounds ();
		/**
		 * Gets a font resource or adds one if it isn't already loaded
		 * @param file resource filename
		 * @return reference to opened sound
		 */
		static shared_ptr<TTF_Font> GetFont (string file, int fontSize);
		/**
		 * Dumps the entire fonts table
		 */
		static void ClearFonts ();
	private:
		static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
		static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
		static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
		static unordered_map<string, shared_ptr<TTF_Font>> fontTable;
};
