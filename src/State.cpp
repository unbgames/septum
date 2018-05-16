#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
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

State::State () {
	started = false;
	quitRequested = false;
	bg.AddComponent(new Sprite(bg, "assets/img/ocean.jpg"));
	bg.AddComponent(new CameraFollower(bg));
	map.AddComponent(
			new TileMap(map, "assets/map/tileMap.txt",
					new TileSet(64, 64, "assets/img/tileset.png", map)));
}

State::~State () {
	objectArray.clear();
}

void State::Start () {
	LoadAssets();
	bg.Start();
	map.Start();
	for (int i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Start();
	}
	music.Play();
	started = true;
}

void State::LoadAssets () {
	music.Open("assets/audio/stageState.ogg");

	GameObject *penguin = new GameObject();
	penguin->box.x = 704;
	penguin->box.y = 640;
	penguin->AddComponent(new PenguinBody(*penguin));


	GameObject *alien = new GameObject();
	alien->box.x = 512;
	alien->box.y = 300;
	alien->AddComponent(new Alien(*alien, 7));
	objectArray.emplace_back(penguin);
	objectArray.emplace_back(alien);

	Camera::Follow(penguin);
}

void State::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	Camera::Update(dt);

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	bg.Update(dt);
	map.Update(dt);
	for (int i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Update(dt);
	}

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

void State::Render () {
	bg.Render();
	map.Render();
	((TileMap*) (map.GetComponent("TileMap")))->RenderLayer(0, Camera::pos.x,
			Camera::pos.y);
	for (auto& go : objectArray) {
		go->Render();
	}
	((TileMap*) (map.GetComponent("TileMap")))->RenderLayer(1, Camera::pos.x,
			Camera::pos.y);
}

bool State::QuitRequested () const {
	return quitRequested;
}

weak_ptr<GameObject> State::AddObject (GameObject* go) {
	shared_ptr<GameObject> ptr(go);
	objectArray.push_back(ptr);
	if (started) {
		go->Start();
	}
	return weak_ptr<GameObject>(ptr);
}

weak_ptr<GameObject> State::GetObjectPtr (GameObject* go) {
	for (auto& it : objectArray) {
		if (it.get() == go) {
			return std::weak_ptr<GameObject>(it);
		}
	}

	return std::weak_ptr<GameObject>();
}
