#include "Face.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
Face::Face (GameObject& associated) :
		Component(associated) {
	hitpoints = 30;
}

void Face::Damage (int damage) {
	// So it can`t keep damaging after death
	if (hitpoints > 0) {
		hitpoints -= damage;
		if (hitpoints <= 0) {
			((Sound*) associated.GetComponent("Sound"))->Play();
		}
	}
}

void Face::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
		if (associated.box.Contains(
				Vec2((float) inputManager.GetMouseX(),
						(float) inputManager.GetMouseY()) + Camera::pos)) {
			Damage(std::rand() % 10 + 10);
		}
	}
	int playing = Mix_Playing(
			((Sound*) associated.GetComponent("Sound"))->GetChannel());
	if (hitpoints <= 0 && !playing) {
		associated.RequestDelete();
	}
}

void Face::Render () {

}

bool Face::Is (string type) const {
	return type == "Face";
}
