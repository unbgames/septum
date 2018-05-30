#include "FirstStageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"

Sprite *jujuba = nullptr;
Sprite *life = nullptr;
Sprite *lifepoints = nullptr;
bool demonio = false;

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
	HUDcara->box.x = 0;
	HUDcara->box.y = 0;
	jujuba = new Sprite(*HUDcara,"assets/img/HUDface.png");
	jujuba->SetScale(0.6,0.6);
	HUDcara->AddComponent(jujuba);
	AddObject(HUDcara);
	GameObject *HUDLife = new GameObject();
	HUDLife->box.x = 200;
	HUDLife->box.y = 0;
	life = new Sprite(*HUDLife,"assets/img/HUDbox.png");
	HUDLife->AddComponent(life);
	AddObject(HUDLife);
	GameObject *HUDLifepoints = new GameObject();
	HUDLifepoints->box.x = 208;
	HUDLifepoints->box.y = 8;
	lifepoints = new Sprite(*HUDLifepoints,"assets/img/HUDlife.png");
	lifepoints->SetScale(9.65,0.085);
	HUDLife->AddComponent(lifepoints);
	AddObject(HUDLifepoints);



}
void FirstStageState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	if(MainCharacter::mainCharacter->demon != demonio){
		demonio = MainCharacter::mainCharacter->demon;
		if(demonio)
			jujuba->Open("assets/img/HUDdemon.png");
		else
			jujuba->Open("assets/img/HUDface.png");
	}
	lifepoints->SetScale(0.0965*MainCharacter::mainCharacter->hp,0.085);
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
