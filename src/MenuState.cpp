#include "MenuState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "FirstStageState.h"


MenuState::MenuState () {
}
MenuState::~MenuState () {

}

void MenuState::LoadAssets () {
	GameObject *splashScreen = new GameObject();
	splashScreen->AddComponent(
			new Sprite(*splashScreen, "assets/img/septem.png"));
	splashScreen->AddComponent(new CameraFollower(*splashScreen));
	AddObject(splashScreen);

}
void MenuState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if(inputManager.KeyPress(' ')){
		Game& game = Game::GetInstance();
		game.Push(new FirstStageState());
	}

	UpdateArray(dt);
	Camera::Update(dt);
}
void MenuState::Render () {
	RenderArray();
}

void MenuState::Start () {
	LoadAssets();
	StartArray();
	started = true;
}
void MenuState::Pause () {

}
void MenuState::Resume () {
	// Camera::pos = {0, 0};
}
