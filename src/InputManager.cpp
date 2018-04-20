#include "InputManager.h"

InputManager& InputManager::GetInstance () {
	static InputManager instance;
	return instance;
}

InputManager::InputManager () :
		mouseState { false }, mouseUpdate { 0 } {
	updateCounter = 0;
	quitRequested = false;
	mouseX = 0;
	mouseY = 0;
}

InputManager::~InputManager () {
	keyState.clear();
	keyUpdate.clear();
}

void InputManager::Update () {
	SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	quitRequested = false;
	updateCounter++;
	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.repeat != 1) {
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		}
		if (event.type == SDL_KEYUP) {
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}
	}

}

bool InputManager::KeyPress (int key) {
	return keyUpdate[key] == updateCounter && keyState[key];
}

bool InputManager::KeyRelease (int key) {
	return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::IsKeyDown (int key) {
	return keyState[key];
}

bool InputManager::MousePress (int button) const {
	return mouseUpdate[button] == updateCounter && mouseState[button];

}
bool InputManager::MouseRelease (int button) const {
	return mouseUpdate[button] == updateCounter && !mouseState[button];
}

bool InputManager::IsMouseDown (int button) const {
	return mouseState[button];
}

int InputManager::GetMouseX () const {
	return mouseX;
}

int InputManager::GetMouseY () const {
	return mouseY;
}

bool InputManager::QuitRequested () const {
	return quitRequested;
}
