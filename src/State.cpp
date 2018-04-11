#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Sprite.h"
#include "Face.h"
#include "Vec2.h"
#include "Sound.h"
#include <math.h>

State::State () {
	quitRequested = false;
	LoadAssets();
	music.Play();
}

State::~State () {
	objectArray.clear();
}

void State::Input () {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (int i = objectArray.size() - 1; i >= 0; --i) {
				GameObject* go = (GameObject*) objectArray[i].get();

				if (go->box.Contains(Vec2((float) mouseX, (float) mouseY))) {
					Face* face = (Face*) go->GetComponent("Face");
					if (nullptr != face) {
						face->Damage(std::rand() % 10 + 10);
						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}
			else {
				Vec2 objPos = Vec2(200, 0).GetRotated(
						-M_PI + M_PI * (rand() % 1001) / 500.0)
						+ Vec2(mouseX, mouseY);
				AddObject((int) objPos.x, (int) objPos.y);
			}
		}
	}
}

void State::LoadAssets () {
	GameObject *bg = new GameObject();
	bg->AddComponent(
			new Sprite(*bg, "assets/img/ocean.jpg"));
	GameObject *map = new GameObject();
	map->AddComponent(
			new TileMap(*map, "assets/map/tileMap.txt",
					new TileSet(64, 64, "assets/img/tileset.png", *map)));
	objectArray.emplace_back(bg);
	objectArray.emplace_back(map);
	music.Open("assets/audio/stageState.ogg");
}

void State::Update (float dt) {
	Input();
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
