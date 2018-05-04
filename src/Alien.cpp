#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"

#define ALIEN_ROTATION -0.6

Alien::Alien (GameObject& associated, int nMinions) :
		Component(associated), hp(30), speed(100, 100), nMinions(nMinions) {
	Sprite* spr = new Sprite(associated, "assets/img/alien.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
}

void Alien::Start () {
	for (int m = 0; m < nMinions; ++m) {
		float offset = 2 * M_PI * m / nMinions;
		GameObject* go = new GameObject();
		go->AddComponent(
				new Minion(*go,
						Game::GetInstance().GetState().GetObjectPtr(
								&associated), offset));
		minionArray.emplace_back(
				Game::GetInstance().GetState().AddObject(go));
	}
}

Alien::~Alien () {
	minionArray.clear();
}

Alien::Action::Action (ActionType type, float x, float y) :
		type(type), pos(x, y) {

}

void Alien::Update (float dt) {
	associated.angleDeg += ALIEN_ROTATION;
	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
		taskQueue.emplace(Action::SHOOT,
				(float) inputManager.GetMouseX() + Camera::pos.x,
				(float) inputManager.GetMouseY() + Camera::pos.y);
	}
	if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
		taskQueue.emplace(Action::MOVE,
				(float) inputManager.GetMouseX() + Camera::pos.x,
				(float) inputManager.GetMouseY() + Camera::pos.y);
	}
	if (!taskQueue.empty()) {
		Action task = taskQueue.front();
		if (task.type == Action::MOVE) {
			if (task.pos.GetDistance(associated.box.GetCenter())
					> speed.GetLength() * dt) {
				Vec2 dir = (task.pos - associated.box.GetCenter()).GetUnit();
				Vec2 dirUnit = dir.GetUnit();
				dir.x *= speed.x * abs(dirUnit.x);
				dir.y *= speed.y * abs(dirUnit.y);

				associated.box.x += (dir.x * dt);
				associated.box.y += (dir.y * dt);
			}
			else {
				associated.box.x = task.pos.x - associated.box.w / 2;
				associated.box.y = task.pos.y - associated.box.h / 2;
				taskQueue.pop();
			}
		}
		else if (task.type == Action::SHOOT) {
			shared_ptr<GameObject> attacker;
			float minDistance = HUGE_VALF;
			for (auto& it : minionArray) {
				float distance = it.lock()->box.GetCenter().GetDistance(
						task.pos);
				if (distance < minDistance) {
					minDistance = distance;
					attacker = it.lock();
				}
			}
			Minion* minion =
					(Minion*) (attacker->GetComponent(
							"Minion"));
			minion->Shoot(task.pos);
			taskQueue.pop();
		}
	}
	if (hp <= 0) {
		associated.RequestDelete();
	}
}

void Alien::Render () {

}

bool Alien::Is (string type) const {
	return type == "Alien";
}
