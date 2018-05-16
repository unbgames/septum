#include "PenguinBody.h"
#include "Sprite.h"
#include "GameObject.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>
#include <math.h>

#define PENGUIN_ACCELERATION 6
#define PENGUIN_SPEED_LIMIT 300
#define PENGUIN_ANGULAR_VELOCITY M_PI / 12

using std::weak_ptr;

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody (GameObject& associated) :
		Component(associated), hp(70), angle(0), linearSpeed(0) {
	player = this;
	Sprite* spr = new Sprite(associated, "assets/img/penguin.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

}
PenguinBody::~PenguinBody () {
	player = nullptr;

}

void PenguinBody::Start () {

	GameObject* go = new GameObject();
	pcannon = Game::GetInstance().GetState().AddObject(go);
	go->AddComponent(
			new PenguinCannon(*go,
					Game::GetInstance().GetState().GetObjectPtr(&associated)));
}
void PenguinBody::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.IsKeyDown('a') || inputManager.IsKeyDown('d')) {
		int direction = inputManager.IsKeyDown('d') ? 1 : -1;
		angle += direction * PENGUIN_ANGULAR_VELOCITY;
		associated.angleDeg = angle * (180 / M_PI);
	}
	if (inputManager.IsKeyDown('w') || inputManager.IsKeyDown('s')) {
		int direction = inputManager.IsKeyDown('w') ? 1 : -1;
		linearSpeed += direction * PENGUIN_ACCELERATION;
		if (linearSpeed > PENGUIN_SPEED_LIMIT) {
			linearSpeed = PENGUIN_SPEED_LIMIT;
		}
		else if (linearSpeed < -PENGUIN_SPEED_LIMIT) {
			linearSpeed = -PENGUIN_SPEED_LIMIT;
		}
	}
	else {
		if (linearSpeed < 0) {
			linearSpeed =
					linearSpeed > -PENGUIN_ACCELERATION ?
							0 : linearSpeed + PENGUIN_ACCELERATION;
		}
		else if (linearSpeed > 0) {
			linearSpeed =
					linearSpeed < PENGUIN_ACCELERATION ?
							0 : linearSpeed - PENGUIN_ACCELERATION;
		}
	}
	if (linearSpeed) {
		Vec2 dir = { linearSpeed, 0 };
		dir = dir.GetRotated(angle);
		associated.box.x += (dir.x * dt);
		associated.box.y += (dir.y * dt);
		pcannon.lock()->box.x += (dir.x * dt);
		pcannon.lock()->box.y += (dir.y * dt);
	}
	if (hp <= 0) {
		associated.RequestDelete();
		pcannon.lock()->RequestDelete();
	}

}
void PenguinBody::Render () {

}

bool PenguinBody::Is (string type) const {
	return type == "PenguinBody";
}
