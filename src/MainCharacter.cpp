#include "MainCharacter.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Colliders.h"
#include "State.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "Collision.h"

using std::weak_ptr;

#define CHARACTER_SPEED 650
#define GRAVITY 2500
#define NORMAL_ATTACK_HIT_FRAME_START 0.450
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
int ISBLOCKED = 0;
bool CantWalk = false;
Vec2 Bloqueiotela = {0,1286};

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Component(associated),characterState(IDLE),demon(false) {
	mainCharacter = this;
	hp = 100;
	furia = 100;
	spr = new Sprite(associated, "assets/img/player_idle.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

	colliders = new Colliders(associated);
	Collider* collisionbox = new Collider(associated,{0.7,0.8});
	Collider* weaponCollider = new Collider(associated,{0,0}, {0, 0});
	colliders->AddCollider("body", collisionbox);
	colliders->AddCollider("hand", weaponCollider);

	associated.AddComponent(colliders);
}
MainCharacter::~MainCharacter () {
	mainCharacter = nullptr;

}

void MainCharacter::Start () {
}
void MainCharacter::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	animationTimer.Update(dt);
	float currentTime = animationTimer.Get();
	int dir;
	int attackIssued = false;
	if (inputManager.KeyPress('k')) {
		attackIssued = true;
	}
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
	if(demon)
		furia-=0.1;
	if(furia<0){
		furia=0;
		demon = false;
	}
	if (furia>100)
		furia=100;

	if(inputManager.KeyRelease('u') && !demon){
		if(hp+furia>=100){
			furia += hp - 100;
			hp = 100;
		}else{
			hp+=furia;
			furia=0;
		}
	}

	if (speed.x < 0) {
		associated.flipHorizontal = true;
	} else if (speed.x > 0) {
		associated.flipHorizontal = false;
	}

	if (speed.y == 0 && inputManager.KeyPress('w')) {
		speed.y = 1000;
	} else {
		speed.y -= GRAVITY * dt;
	}

	associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);

	if (associated.box.y > 250 + ISBLOCKED) {
		speed.y = 0;
		associated.box.y = 250+ISBLOCKED;
	}

	if (CantWalk) {
			associated.box.x -= (speed.x * dt);
	}

	if (!attacking) {
		if(inputManager.IsKeyDown('s')){
	  		changeState(attackIssued ? CROUCH_ATTACK : CROUCH);
	  		furia+=0.5;
	  	}else if(inputManager.IsKeyDown('j')){
	  		changeState(BLOCK);
		}
	  	else if(associated.box.y < 250){
			changeState(attackIssued ? JUMP_ATTACK : JUMP);
		}else if(dir != 0){
			changeState(attackIssued ? ATTACK : WALK);
		}else if(speed.x == 0 && speed.y==0){
			changeState(attackIssued ? ATTACK : IDLE);
		}
		if (attackIssued) {
			attacking = true;
		}
	}

	if (characterState == ATTACK) {
		if (NORMAL_ATTACK_HIT_FRAME_START >= (currentTime - dt) && NORMAL_ATTACK_HIT_FRAME_START <= currentTime) {
			colliders->GetCollider("hand")->SetScale({0.45, 0.3});
			colliders->GetCollider("hand")->SetOffset({210, 40});
		} else if (NORMAL_ATTACK_HIT_FRAME_END >= (currentTime - dt) && NORMAL_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("hand")->SetScale({0,0});
			colliders->GetCollider("hand")->SetOffset({0,0});
		}
	}

	if(associated.box.x > 640 + Camera::pos.x/2 && speed.x > 0)
		Camera::Follow(&associated);
	if(associated.box.x <640 + Camera::pos.x && speed.x <0)
		Camera::Follow(&associated);

	if(associated.box.x > Bloqueiotela.y  && Camera::IsFollowing()){
		Camera::Unfollow();
		if(associated.box.x > Bloqueiotela.y + 512){
			associated.box.x = Bloqueiotela.y+ 512;
		}
	}
	else if(associated.box.x < Bloqueiotela.x + 512){
		Camera::Unfollow();
		if(associated.box.x < Bloqueiotela.x){
			associated.box.x = Bloqueiotela.x;
		}
	}
	else{
		associated.box.x = associated.box.x;
	}

	if (stateChanged) {
		StateLogic();
	}
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter";
}
void MainCharacter::changeState(stateType state){
	if(characterState != state){
		// if(state == BLOCK){
		// 	associated.box.y -=110;
		// 	ISBLOCKED = -110;
		// }
		// else if(characterState == BLOCK){
		// 	associated.box.y+=100;
		// 	ISBLOCKED = 0;
		// }
		characterState = state;
		stateChanged = true;
	}
}

void MainCharacter::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		if (idCollider == "body" && idOtherCollider == "body") {
			if(characterState!=WALK){
				if(colliders->GetCollider("body")->box.x+colliders->GetCollider("body")->box.w/2>otherCollider->box.x+otherCollider->box.w/2)
				associated.box.x = otherCollider->box.x + otherCollider->box.w;
				else{
					associated.box.x =(otherCollider->box.x - associated.box.w);
				}
				CantWalk = true;
			}
			CantWalk = false;
		}
	}
}

void MainCharacter::NotifyAnimationEnd () {
	animationTimer.Restart();
	if (attacking) {
		attacking = false;
	}
}

void MainCharacter::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/player_idle.png");
		spr->SetFrameCount(1);
	}else if(characterState == JUMP && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		spr->SetFrameCount(7);
		hp-=10;
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/testewalk.png");
		spr->SetFrameCount(8);
	}else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/GenericBLOCK.png");
		spr->SetFrameCount(7);
	}else if(characterState== CROUCH && stateChanged){
		spr->Open("assets/img/GenericCROUCH.png");
		spr->SetFrameCount(7);
	}else if(characterState== ATTACK && stateChanged){
		spr->Open("assets/img/GenericATTACK.png");
		spr->SetFrameCount(7);
	}else if(characterState== JUMP_ATTACK && stateChanged){
		spr->Open("assets/img/GenericCROUCH.png");
		spr->SetFrameCount(7);
	}else if(characterState== CROUCH_ATTACK && stateChanged){
		spr->Open("assets/img/GenericBLOCK.png");
		spr->SetFrameCount(7);
	}
	// associated.box.h = spr->GetHeight();
	// associated.box.w = spr->GetWidth();
	stateChanged = false;
}
