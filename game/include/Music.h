#pragma once
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

/**
 * Class for game Music
 */
class Music {
	public:
		Music ();
		~Music ();
		/**
		 * Music constructor
		 * @param file audio file
		 */
		Music (string file);

		/**
		 * Plays audio
		 * @param times The amount of times the audio will loop. -1 for infinite loop.
		 */
		void Play (int times = -1);

		/**
		 * Stops audio
		 * @param msToStop fade time
		 */
		void Stop (int msToStop = 1500);

		/**
		 * Opens an audio file
		 * @param file file to open
		 */
		void Open (string file);

		/**
		 * Returns if the file is open
		 * @retval true there is an open file
		 * @retval false there is no file
		 */
		bool isOpen () const;

	private:
		shared_ptr<Mix_Music> music;
};
