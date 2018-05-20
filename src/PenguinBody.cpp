#include "PenguinBody.h"
#include "Sprite.h"
#include "GameObject.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"

#define PENGUIN_ACCELERATION 6
#define PENGUIN_SPEED_LIMIT 300
#define PENGUIN_ANGULAR_VELOCITY M_PI / 12

using std::weak_ptr;

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody (GameObject& associated) :
		Component(associated), hp(50), angle(0), linearSpeed(0) {
	player = this;
	Sprite* spr = new Sprite(associated, "assets/img/penguin.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
}
PenguinBody::~PenguinBody () {
	player = nullptr;

}

void PenguinBody::Start () {

	GameObject* go = new GameObject();
	pcannon = Game::GetInstance().GetCurrentState().AddObject(go);
	go->AddComponent(
			new PenguinCannon(*go,
					Game::GetInstance().GetCurrentState().GetObjectPtr(
							&associated)));
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
		Vec2 result;
		result.x = associated.box.x + (dir.x * dt);
		result.y = associated.box.y + (dir.y * dt);
		associated.box.x = result.x > 1380 ? 1380 : (result.x < 0 ? 0 : result.x);
		associated.box.y = result.y > 1280 ? 1280 : (result.y < 0 ? 0 : result.y);
		pcannon.lock()->box.x = associated.box.x;
		pcannon.lock()->box.y = associated.box.y;
	}
	if (hp <= 0) {

		GameObject* go = new GameObject();
		go->box.x = associated.box.x;
		go->box.y = associated.box.y;
		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/penguindeath.png", 5, 0.3, 1.5));

		Sound* sound = new Sound(*go, "assets/audio/boom.wav");
		go->AddComponent(sound);

		sound->Play();

		Camera::Unfollow();
		associated.RequestDelete();
		pcannon.lock()->RequestDelete();
	}

}
void PenguinBody::Render () {

}

bool PenguinBody::Is (string type) const {
	return type == "PenguinBody";
}

void PenguinBody::NotifyCollision (GameObject& other) {
	Component* bullet = other.GetComponent("Bullet");
	if (bullet != nullptr) {
		if (((Bullet*) bullet)->targetsPlayer) {
			hp -= ((Bullet*) bullet)->GetDamage();
		}
	}
}

Vec2 PenguinBody::GetCenterPosition () const {
	return associated.box.GetCenter();
}
