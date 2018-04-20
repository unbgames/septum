#pragma once
#define INCLUDE_SDL
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#include <unordered_map>
#include "SDL_include.h"
using std::unordered_map;
class InputManager {
	public:
		/**
		 * Updates input state
		 */
		void Update ();
		/**
		 * Checks if a Key was pressed in the current frame
		 * @param key key to be checked
		 * @return whether the key was pressed in the current frame
		 */
		bool KeyPress (int key);
		/**
		 * Checks if a Key was released in the current frame
		 * @param key key to be checked
		 * @return whether the key was released in the current frame
		 */
		bool KeyRelease (int key);
		/**
		 * Checks if a Key is pressed in the current frame
		 * @param key key to be checked
		 * @return whether the key is pressed in the current frame
		 */
		bool IsKeyDown (int key);

		/**
		 * Checks if a mouse button was pressed in the current frame
		 * @param button button to be checked
		 * @return whether the button was pressed in the current frame
		 */
		bool MousePress (int button) const;
		/**
		 * Checks if a mouse button was released in the current frame
		 * @param button button to be checked
		 * @return whether the button was released in the current frame
		 */
		bool MouseRelease (int button) const;
		/**
		 * Checks if a mouse button is pressed in the current frame
		 * @param button button to be checked
		 * @return whether the button is pressed in the current frame
		 */
		bool IsMouseDown (int button) const;

		/**
		 * Return the current x-axis position of the mouse cursor
		 * @return x-axis position of the mouse cursor
		 */
		int GetMouseX () const;
		/**
		 * Return the current y-axis position of the mouse cursor
		 * @return y-axis position of the mouse cursor
		 */
		int GetMouseY () const;

		/**
		 * Returns if input has requested the program exit
		 * @return whether input has requested the program exit
		 */
		bool QuitRequested () const;

		/**
		 * Returns the singleton instance of InputManager
		 * @return InputManager instance
		 */
		static InputManager& GetInstance ();

	private:
		
		InputManager ();
		~InputManager ();

		bool mouseState[6];
		int mouseUpdate[6];

		unordered_map<int, bool> keyState;
		unordered_map<int, int> keyUpdate;
		
		bool quitRequested;

		int updateCounter;

		int mouseX;
		int mouseY;
};
