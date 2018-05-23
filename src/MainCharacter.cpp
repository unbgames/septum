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

#define CHARACTER_SPEED 100

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
  dir *= CHARACTER_SPEED;

  associated.box.x += (dir * dt);
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter";
}
