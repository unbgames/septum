#include "FirstStageState.h"
#include "Sprite.h"
#include "Background.h"
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
#include "Colliders.h"
#include "Corvus.h"
#include "Vulturem.h"

FirstStageState::FirstStageState () {
}
FirstStageState::~FirstStageState () {

}

void FirstStageState::LoadAssets () {
	// GameObject *splashScreen = new GameObject();
	// splashScreen->AddComponent(
	// 		new Sprite(*splashScreen, "assets/img/backgroundHellBeta.png"));
	// splashScreen->AddComponent(new CameraFollower(*splashScreen));
	// AddObject(splashScreen);
	GameObject *background = new GameObject();
	Background* bg = new Background(*background, 0.03);
	bg->AddLayer(new Sprite(*background, "assets/img/sky.png"));
	bg->AddLayer(new Sprite(*background, "assets/img/clouds_1.png"));
	bg->AddLayer(new Sprite(*background, "assets/img/rocks.png"));
	bg->AddLayer(new Sprite(*background, "assets/img/clouds_2.png"));
	bg->AddLayer(new Sprite(*background, "assets/img/rocks_1.png"));
	bg->AddLayer(new Sprite(*background, "assets/img/rocks_2.png"));
	background->AddComponent(bg);
	AddObject(background);

	GameObject *map = new GameObject();
	map->box.y = 60;
	map->AddComponent(
			new TileMap(*map, "assets/map/tileMap.txt",
				new TileSet(256, 128, "assets/img/teste tile1.png", *map),{0,-75}));
	AddObject(map);

	GameObject *character = new GameObject();
	character->AddComponent(
			new MainCharacter(*character));
	character->box.y = 450;
	AddObject(character);

	GameObject *Hud = new GameObject();
	Hud->AddComponent(new HUD(*Hud));
	AddObject(Hud);

	/*GameObject *Human = new GameObject();
	Human->box.x = 500;
	Human->box.y = 450;
	Human->AddComponent(new Humano(*Human));
	GameObject *Human1 = new GameObject();
	Human1->box.x = 500;
	Human1->box.y = 100;
	Human1->AddComponent(new Humano(*Human1));*/
	GameObject *corvo = new GameObject();
	corvo->box.x = 800;
	corvo->box.y = 450;
	corvo->AddComponent(new Corvus(*corvo));
	// AddObject(Human);
	// AddObject(Human1);
	AddObject(corvo);
	GameObject *urubu = new GameObject();
	urubu->box.x = 1100;
	urubu->box.y = 450;
	urubu->AddComponent(new Vulturem(*urubu));
	AddObject(urubu);
}
void FirstStageState::Update (float dt) {
	Camera::Update(dt);
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	for (int i = 0; i < objectArray.size(); ++i) {
		Component* cptA = objectArray[i]->GetComponent("Colliders");
		if (cptA != nullptr) {
			for (int j = i + 1; j < objectArray.size(); ++j) {
				Component* cptB = objectArray[j]->GetComponent("Colliders");
				if (cptB != nullptr) {
					((Colliders*) cptA)->CheckCollision(*objectArray[j].get());
				}
			}
		}
	}
	UpdateArray(dt);

	vector<shared_ptr<GameObject>>::iterator it = objectArray.begin();
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(it + i);
		}
	}


}
void FirstStageState::Render () {
	RenderArray();
	//map.Render();
}

void FirstStageState::Start () {
	Camera::pos = {0, 0};
	LoadAssets();
	StartArray();
	started = true;
}
void FirstStageState::Pause () {

}
void FirstStageState::Resume () {
}
