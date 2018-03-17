#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>

class Music {
	public:
		Music ();
		~Music ();
		Music (std::string file);

		void Play (int times = -1);
		void Stop (int msToStop = 1500);
		void Open (std::string file);
		bool isOpen ();

	private:
		Mix_Music* music;
};
