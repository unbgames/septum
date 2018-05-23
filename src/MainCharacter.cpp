#include "MainCharacter.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"

using std::weak_ptr;

#define CHARACTER_SPEED 650
#define GRAVITY 2000

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Component(associated),characterState(IDLE),demon(false) {
	mainCharacter = this;
	hp = 100;
	furia = 80;
	spr = new Sprite(associated, "assets/img/GenericIDLE.png",7,0.08);
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
	int dir;
  	if(inputManager.IsKeyDown('a')){
  		dir = -1;
  	}else if(inputManager.IsKeyDown('d')){
  		dir = 1;
  	}else{
  		dir = 0;
  	}
  	speed.x = dir * CHARACTER_SPEED;
  	if(inputManager.KeyRelease('i')){
  		demon = demon?false:true;
  	}

	if (speed.x < 0) {
		associated.flipHorizontal = true;
	} else if (speed.x > 0) {
		associated.flipHorizontal = false;
	}

	if (speed.y == 0 && inputManager.KeyPress('w')) {
		speed.y = 800;
	} else {
		speed.y -= GRAVITY * dt;
	}
	associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);

	if (associated.box.y > 350) {
		speed.y = 0;
		associated.box.y = 350;
	}

	if(associated.box.y < 350){
		changeState(JUMP);
	}else if(dir != 0){
		changeState(WALK);
	}else if(speed.x == 0 && speed.y==0){
		changeState(IDLE);
	}

	associated.box.x = associated.box.x > 1100 ? 1100 : associated.box.x < 0 ? 0 : associated.box.x;
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/GenericIDLE.png");
		stateChanged = false;
	}else if(characterState == JUMP && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		hp-=10;
		stateChanged = false;
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/GenericWALK.png");
		stateChanged = false;
		//printf("Andou!\n");
	}
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter";
}
void MainCharacter::changeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}
