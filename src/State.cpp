#include "State.h"

State::State () {
	quitRequested = false;
	LoadAssets();
}

void State::LoadAssets () {
	bg.Open("img/ocean.jpg");
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

