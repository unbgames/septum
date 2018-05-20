#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"

#define TEXT_FADE_TIME 0.4
#define TEXT_SHOW_TIME 0.8

TitleState::TitleState () {
}
TitleState::~TitleState () {

}

void TitleState::LoadAssets () {
	GameObject *splashScreen = new GameObject();
	splashScreen->AddComponent(
			new Sprite(*splashScreen, "assets/img/title.jpg"));
	splashScreen->AddComponent(new CameraFollower(*splashScreen));
	AddObject(splashScreen);

	playText.AddComponent(
			new Text(playText, "assets/font/Call me maybe.ttf", 32,
					Text::BLENDED, "Press spacebar to play", { .r = 0, .g = 0,
							.b = 0, .a = 255 }));
	playText.box.x = 360;
	playText.box.y = 500;

}
void TitleState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if (inputManager.KeyPress(' ')) {
		Game::GetInstance().Push(new StageState());
	}

	textTimer.Update(dt);
	if (textTimer.Get() >= TEXT_SHOW_TIME + TEXT_FADE_TIME) {
		textTimer.Restart();
	}
	UpdateArray(dt);
	playText.Update(dt);
}
void TitleState::Render () {
	RenderArray();
	if (textTimer.Get() < TEXT_SHOW_TIME) {
		playText.Render();
	}
}

void TitleState::Start () {
	LoadAssets();
	StartArray();
	playText.Start();
	started = true;
}
void TitleState::Pause () {

}
void TitleState::Resume () {
	Camera::pos = {0, 0};
}
