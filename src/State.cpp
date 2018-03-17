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
	quitRequested = dt;
}

void State::Render () {
	bg.Render(0, 0);
}

bool State::QuitRequested () {
	return quitRequested;
}

