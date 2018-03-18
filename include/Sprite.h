#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>

using std::string;

/**
 * Class for game image
 */
class Sprite {
	public:
		Sprite ();

		/**
		 * Sprite constructor
		 * @param file image file
		 */
		Sprite (string file);
		~Sprite ();

		/**
		 * Opens an image file
		 * @param file image file
		 */
		void Open (string file);

		/**
		 * Sets clipping rectangle
		 * @param x position on the x-axis of the rectangle left-upper corner
		 * @param y position on the y-axis of the rectangle left-upper corner
		 * @param w rectangle width
		 * @param h rectangle height
		 */
		void SetClip (int x, int y, int w, int h);

		/**
		 * Renders the Sprite on the window
		 * @param x x-axis screen position
		 * @param y y-axis screen position
		 */
		void Render (int x, int y);

		int GetWidth () const;
		int GetHeight () const;

		/**
		 * Returns if the file is open
		 * @retval true there is an open file
		 * @retval false there is no file
		 */
		bool IsOpen () const;

	private:
		SDL_Texture* texture;
		int width = 0;
		int height = 0;
		SDL_Rect clipRect;
};
