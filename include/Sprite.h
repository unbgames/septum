#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include "Vec2.h"
#include "Timer.h"
#include "Component.h"
#include <memory>

using std::string;
using std::shared_ptr;

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
		Sprite (GameObject& associated, string file, int frameCount = 1,
				float frameTime = 1, float secondsToSelfDestruct = 0);
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

		/**
		 * Sets the scale of the Sprite
		 * @param scaleX horizontal scale
		 * @param scaleY vertical scale
		 */
		void SetScale (float scaleX, float scaleY);

		/**
		 * Gets the current scale of the Sprite
		 * @return Sprite scale
		 */
		Vec2 GetScale () const;

		void SetFrame (int frame);
		void SetFrameCount (int frameCount);
		void SetFrameTime (float frameTime);

	private:
		shared_ptr<SDL_Texture> texture;
		int width = 0;
		int height = 0;
		SDL_Rect clipRect;
		Vec2 scale;
		int frameCount = 1;
		int currentFrame = 0;
		float timeElapsed = 0;
		float frameTime = 1;
		Timer selfDestructCount;
		float secondsToSelfDestruct = 0;
};
