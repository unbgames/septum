#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "Sprite.h"

State::State () {
	quitRequested = false;
	LoadAssets();
	music.Play();
}

void State::LoadAssets () {
	Sprite* sprite = new Sprite(bg, "assets/img/ocean.jpg");
	bg.AddComponent(sprite);
	music.Open("assets/audio/stageState.ogg");
}

void State::Update (float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render () {
	bg.Render();
}

bool State::QuitRequested () const{
	return quitRequested;
}
