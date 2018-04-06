#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include "Component.h"

using std::string;

/**
 * Class for game image
 */
class Sprite : public Component{
	public:
		Sprite (GameObject& associated);

		/**
		 * Sprite constructor
		 * @param associated GameObjected that encapsulates the sprite
		 * @param file image file
		 */
		Sprite (GameObject& associated, string file);
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
		 */
		void Render ();

		/**
		 * Renders the Sprite based on a position
		 * @param x x-axis coordinate
		 * @param y y-axis coordinate
		 */
		void Render (float x, float y);

		int GetWidth () const;
		int GetHeight () const;

		/**
		 * Returns if the file is open
		 * @retval true there is an open file
		 * @retval false there is no file
		 */
		bool IsOpen () const;

		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @retval true the passed type is Sprite
		 * @retval false the passed type is not Sprite
		 */
		bool Is (string type) const;

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);

	private:
		SDL_Texture* texture;
		int width = 0;
		int height = 0;
		SDL_Rect clipRect;
};
