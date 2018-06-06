#include "FirstStageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "HUD.h"


FirstStageState::FirstStageState () {
}
FirstStageState::~FirstStageState () {

}

void FirstStageState::LoadAssets () {
	GameObject *splashScreen = new GameObject();
	splashScreen->AddComponent(
			new Sprite(*splashScreen, "assets/img/backgroundHellBeta.png"));
	splashScreen->AddComponent(new CameraFollower(*splashScreen));
	AddObject(splashScreen);

	GameObject *character = new GameObject();
	character->AddComponent(
			new MainCharacter(*character));
	character->box.y = 350;
	AddObject(character);

	GameObject *Hud = new GameObject();
	Hud->AddComponent(new HUD(*Hud));
	AddObject(Hud);
}
void FirstStageState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	UpdateArray(dt);
	Camera::Update(dt);
}
void FirstStageState::Render () {
	RenderArray();
}

void FirstStageState::Start () {
	LoadAssets();
	StartArray();
	started = true;
}
void FirstStageState::Pause () {

}
void FirstStageState::Resume () {
	// Camera::pos = {0, 0};
}
