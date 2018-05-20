#define INCLUDE_SDL
#include "SDL_include.h"
#include "StageState.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <algorithm>
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"
#include "GameData.h"
#include "Game.h"
#include "EndState.h"

StageState::StageState () {
	bg.AddComponent(new Sprite(bg, "assets/img/ocean.jpg"));
	bg.AddComponent(new CameraFollower(bg));
	map.AddComponent(
			new TileMap(map, "assets/map/tileMap.txt",
					new TileSet(64, 64, "assets/img/tileset.png", map)));
}

StageState::~StageState () {
	objectArray.clear();
}

void StageState::Start () {
	LoadAssets();
	bg.Start();
	map.Start();
	StartArray();
	music.Play();
	started = true;
}

void StageState::Pause () {

}

void StageState::Resume () {

}

void StageState::LoadAssets () {
	music.Open("assets/audio/stageState.ogg");

	GameObject *penguin = new GameObject();
	penguin->box.x = 704;
	penguin->box.y = 640;
	penguin->AddComponent(new PenguinBody(*penguin));
	AddObject(penguin);

	int alienCount = rand() % 3 + 1;
	for (int var = 0; var < alienCount; ++var) {
		GameObject *alien = new GameObject();
		alien->box.x = rand() % 1408;
		alien->box.y = rand() % 1280;
		alien->AddComponent(new Alien(*alien, 7, var));
		AddObject(alien);
	}

	Camera::Follow(penguin);
}

void StageState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	Camera::Update(dt);

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	if (Alien::alienCount <= 0) {
		popRequested = true;
		GameData::playerVictory = true;
		Game::GetInstance().Push(new EndState());
	}
	else if (!PenguinBody::player) {
		popRequested = true;
		GameData::playerVictory = false;
		Game::GetInstance().Push(new EndState());
	}

	bg.Update(dt);
	map.Update(dt);
	UpdateArray(dt);

	for (int i = 0; i < objectArray.size(); ++i) {
		Component* cptA = objectArray[i]->GetComponent("Collider");
		if (cptA != nullptr) {
			for (int j = i + 1; j < objectArray.size(); ++j) {
				Component* cptB = objectArray[j]->GetComponent("Collider");
				if (cptB != nullptr) {
					if (Collision::IsColliding(((Collider*) cptA)->box,
							((Collider*) cptB)->box,
							objectArray[i]->angleDeg * M_PI / 180,
							objectArray[j]->angleDeg * M_PI / 180)) {
						objectArray[i]->NotifyCollision(*objectArray[j].get());
						objectArray[j]->NotifyCollision(*objectArray[i].get());
					}
				}
			}
		}
	}

	vector<shared_ptr<GameObject>>::iterator it = objectArray.begin();
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(it + i);
		}
	}
}

void StageState::Render () {
	bg.Render();
	map.Render();
	((TileMap*) (map.GetComponent("TileMap")))->RenderLayer(0, Camera::pos.x,
			Camera::pos.y);
	RenderArray();
	((TileMap*) (map.GetComponent("TileMap")))->RenderLayer(1, Camera::pos.x,
			Camera::pos.y);
}
