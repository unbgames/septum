#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"

Alien::Alien (GameObject& associated, int nMinions) :
		Component(associated), hp(30), speed(50, 50) {
	Sprite* spr = new Sprite(associated, "assets/img/alien.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
}

void Alien::Start () {

}

Alien::~Alien () {

}

Alien::Action::Action (ActionType type, float x, float y) :
		type(type), pos(x, y) {

}

void Alien::Update (float dt) {
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

				dir.x *= speed.x;
				dir.y *= speed.y;

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
