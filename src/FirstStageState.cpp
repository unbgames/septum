#include "FirstStageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "HUD.h"
#include "Humano.h"
#include "TileSet.h"
#include "TileMap.h"

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

	GameObject *map = new GameObject();
	map->box.y = 60;
	map->AddComponent(
			new TileMap(*map, "assets/map/tileMap.txt",
				new TileSet(256, 128, "assets/img/teste tile1.png", *map),{0,-75}));
	AddObject(map);

	GameObject *character = new GameObject();
	character->AddComponent(
			new MainCharacter(*character));
	character->box.y = 250;
	AddObject(character);

	GameObject *Hud = new GameObject();
	Hud->AddComponent(new HUD(*Hud));
	AddObject(Hud);

	GameObject *Human = new GameObject();
	Human->box.x = 500;
	Human->box.y = 450;
	Human->AddComponent(new Humano(*Human));
	AddObject(Human);
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
	//map.Render();
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
