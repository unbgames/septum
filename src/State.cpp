#include "State.h"

State::State () {
	quitRequested = false;
}

void State::LoadAssets () {
// load bg
// load music
}

void State::Update (float dt) {
	quitRequested = dt;
}

void State::Render () {
//	Render bg
}

bool State::QuitRequested () {
	return quitRequested;
}

