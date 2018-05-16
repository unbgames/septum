#include "PenguinCannon.h"
#include "Sprite.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include <math.h>

using std::weak_ptr;

#define CANNON_DISTANCE 50

PenguinCannon::PenguinCannon (GameObject& associated,
		weak_ptr<GameObject> pbody) :
		Component(associated), angle(0), pbody(pbody) {
	Sprite* spr = new Sprite(associated, "assets/img/cubngun.png");
	associated.AddComponent(spr);
	associated.box.w = spr->GetWidth();
	associated.box.h = spr->GetHeight();

	auto go = pbody.lock();

	Vec2 pos = go->box.GetCenter();
	associated.box.x = pos.x - associated.box.w / 2;
	associated.box.y = pos.y - associated.box.h / 2;
}

void PenguinCannon::Update (float dt) {

	auto go = pbody.lock();

	if (!go) {
		associated.RequestDelete();
	}
	else {
		Vec2 pos = go->box.GetCenter();
		InputManager& inputManager = InputManager::GetInstance();
		Vec2 mousePos = { (float) inputManager.GetMouseX() + Camera::pos.x,
				(float) inputManager.GetMouseY() + Camera::pos.y };

		angle = mousePos.GetAngle(pos);
		associated.angleDeg = angle * (180 / M_PI);
		associated.box.x = pos.x - associated.box.w / 2;
		associated.box.y = pos.y - associated.box.h / 2;

		if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
			Shoot();
		}
	}
}
void PenguinCannon::Render () {

}

bool PenguinCannon::Is (string type) const {
	return type == "PenguinCannon";
}

void PenguinCannon::Shoot () {
	
	GameObject* go = new GameObject();
	go->AddComponent(
			new Bullet(*go, angle, 300, 5, 600, "assets/img/penguinbullet.png",
					4, 0.5));
	Vec2 cannonCenter = associated.box.GetCenter()
			+ Vec2(CANNON_DISTANCE, 0).GetRotated(angle);
	go->box.x = cannonCenter.x - go->box.w / 2;
	go->box.y = cannonCenter.y - go->box.h / 2;
	Game::GetInstance().GetState().AddObject(go);

}
