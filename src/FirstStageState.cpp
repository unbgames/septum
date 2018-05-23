#include "FirstStageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"

Sprite *jujuba = nullptr;

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
	GameObject *HUDcara = new GameObject();
	jujuba = new Sprite(*HUDcara,"assets/img/HUDface.png");
	HUDcara->AddComponent(jujuba);
	AddObject(HUDcara);

}
void FirstStageState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	if(MainCharacter::mainCharacter->demon){
		jujuba->Open("assets/img/HUDdemon.png");
	}

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
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
