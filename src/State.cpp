#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

State::State () {
	quitRequested = false;
	LoadAssets();
	music.Play();
}

void State::LoadAssets () {
	bg.Open("assets/img/ocean.jpg");
	music.Open("assets/audio/stageState.ogg");
}

void State::Update (float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render () {
	bg.Render(0, 0);
}

bool State::QuitRequested () const{
	return quitRequested;
}
