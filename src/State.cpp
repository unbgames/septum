#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Sprite.h"
#include "Face.h"
#include "Vec2.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <math.h>

State::State () {
	quitRequested = false;
	LoadAssets();
	music.Play();
	map.AddComponent(
			new TileMap(map, "assets/map/tileMap.txt",
					new TileSet(64, 64, "assets/img/tileset.png", map)));
}

State::~State () {
	objectArray.clear();
}

void State::LoadAssets () {
	GameObject *bg = new GameObject();
	bg->AddComponent(
			new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	GameObject *map = new GameObject();
	map->AddComponent(
			new TileMap(*map, "assets/map/tileMap.txt",
					new TileSet(64, 64, "assets/img/tileset.png", *map)));
	objectArray.emplace_back(bg);
	objectArray.emplace_back(map);
	music.Open("assets/audio/stageState.ogg");
}

void State::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	Camera::Update(dt);

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if (inputManager.KeyPress(' ')) {
		Vec2 objPos = Vec2(200, 0).GetRotated(
				-M_PI + M_PI * (rand() % 1001) / 500.0)
				+ (Vec2(inputManager.GetMouseX(), inputManager.GetMouseY())
						+ Camera::pos);
		AddObject((int) objPos.x, (int) objPos.y);
	}
	map.Update(dt);
	for (int i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Update(dt);
	}

	vector<unique_ptr<GameObject>>::iterator it = objectArray.begin();
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(it + i);
		}
	}
}

void State::Render () {
	map.Render();
	for (auto& go : objectArray) {
		go->Render();
	}
}

bool State::QuitRequested () const {
	return quitRequested;
}

void State::AddObject (int mouseX, int mouseY) {
	GameObject* go = new GameObject();
	Sprite* spr = new Sprite(*go, "assets/img/penguinface.png");
	go->AddComponent(spr);
	go->box.x = mouseX - (spr->GetWidth() / 2);
	go->box.y = mouseY - (spr->GetHeight() / 2);
	go->box.h = spr->GetHeight();
	go->box.w = spr->GetWidth();

	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
	go->AddComponent(new Face(*go));

	objectArray.emplace_back(go);
}
