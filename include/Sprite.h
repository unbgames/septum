#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>

using std::string;

class Sprite {
	public:
		Sprite ();
		Sprite (string file);
		~Sprite ();
		void Open (string file);
		void SetClip (int x, int y, int w, int h);
		void Render (int x, int y);
		int GetWidth ();
		int GetHeight ();
		bool IsOpen ();

	private:
		SDL_Texture* texture;
		int width = 0;
		int height = 0;
		SDL_Rect clipRect;
};
