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
		void Update ();
		bool KeyPress (int key);
		bool KeyRelease (int key);
		bool IsKeyDown (int key);

		bool MousePress (int button) const;
		bool MouseRelease (int button) const;
		bool IsMouseDown (int button) const;

		int GetMouseX () const;
		int GetMouseY () const;

		bool QuitRequested () const;

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
