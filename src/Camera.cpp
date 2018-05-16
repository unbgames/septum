#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(100, 100);
GameObject* Camera::focus = nullptr;

void Camera::Follow (GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow () {
	focus = nullptr;
}

void Camera::Update (float dt) {
	if (focus != nullptr) {
		pos.x = float(
				focus->box.GetCenter().x - Game::GetInstance().GetWidth() / 2);
		pos.y = float(
				focus->box.GetCenter().y - Game::GetInstance().GetHeight() / 2);
	}
	else {
		InputManager& inputManager = InputManager::GetInstance();
		Vec2 dir;
		dir.x = inputManager.IsKeyDown(LEFT_ARROW_KEY) ? -1 : 0;
		dir.x += inputManager.IsKeyDown(RIGHT_ARROW_KEY) ? 1 : 0;

		dir.y = inputManager.IsKeyDown(UP_ARROW_KEY) ? -1 : 0;
		dir.y += inputManager.IsKeyDown(DOWN_ARROW_KEY) ? 1 : 0;

		dir.x *= speed.x;
		dir.y *= speed.y;

		pos += (dir * dt);
	}
}
