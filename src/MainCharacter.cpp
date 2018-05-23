#include "MainCharacter.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"

using std::weak_ptr;

#define CHARACTER_SPEED 200
#define GRAVITY 1000

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Component(associated) {
	mainCharacter = this;
	Sprite* spr = new Sprite(associated, "assets/img/player_indle.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
}
MainCharacter::~MainCharacter () {
	mainCharacter = nullptr;

}

void MainCharacter::Start () {
}
void MainCharacter::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
  int dir = inputManager.IsKeyDown('a') ? -1 : 0;
  dir += inputManager.IsKeyDown('d') ? 1 : 0;
  speed.x = dir * CHARACTER_SPEED;

	if (speed.x < 0) {
		associated.flipHorizontal = true;
	} else if (speed.x > 0) {
		associated.flipHorizontal = false;
	}

	if (speed.y == 0 && inputManager.KeyPress('w')) {
		speed.y = 300;
	} else {
		speed.y -= GRAVITY * dt;
	}
	associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);

	if (associated.box.y > 350) {
		speed.y = 0;
		associated.box.y = 350;
	}
	associated.box.x = associated.box.x > 1100 ? 1100 : associated.box.x < 0 ? 0 : associated.box.x;
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter";
}
