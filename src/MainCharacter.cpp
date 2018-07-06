#include "MainCharacter.h"
#include "Character.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Colliders.h"
#include "State.h"
#include "Damageable.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "Collision.h"

using std::weak_ptr;

#define CHARACTER_SPEED 650
#define GRAVITY 1900
#define NORMAL_ATTACK_HIT_FRAME_START 0.600
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 35

#define CROUCH_ATTACK_HIT_FRAME_START 0.600
#define CROUCH_ATTACK_HIT_FRAME_END 0.650
#define CROUCH_ATTACK_DAMAGE 100

#define JUMP_ATTACK_HIT_FRAME_START 0.300
#define JUMP_ATTACK_HIT_FRAME_END 0.350
#define JUMP_ATTACK_DAMAGE 50
#define FLOOR_HEIGHT 450

#define BLOCK_REDUCTION 1

bool ENEMY_HIT = false;
bool ENEMY_BLOCKED = false;

Vec2 Bloqueiotela = {0,1286};

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Damageable(associated, 100),characterState(IDLE),demon(false) {
	mainCharacter = this;
	furia = 100;
	Character* crt = new Character(associated, Character::PLAYER);
	associated.AddComponent(crt);
	spr = new Sprite(associated, "assets/img/HERO_IDLE.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

	colliders = new Colliders(associated);
	Collider* collisionbox = new Collider(associated, {0.5,0.8}, {-55, 0});
	Collider* weaponCollider = new Collider(associated, {0,0}, {0, 0}, false);
	colliders->AddCollider("body", collisionbox);
	colliders->AddCollider("weapon", weaponCollider);
	associated.AddComponent(colliders);
}
MainCharacter::~MainCharacter () {
	mainCharacter = nullptr;
	Camera::Unfollow();
}

void MainCharacter::Start () {
}
void MainCharacter::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	animationTimer.Update(dt);
	float currentTime = animationTimer.Get();
	int dir = 0;
	int attackIssued = false;
	int blocking = inputManager.IsKeyDown('j');
	if (inputManager.KeyPress('k')) {
		attackIssued = true;
	}

	if (speed.y != 0) {
		speed.y -= GRAVITY * dt;
	}

	if (!blocking) {
		if(inputManager.IsKeyDown('a')){
			dir = -1;
		}else if(inputManager.IsKeyDown('d')){
			dir = 1;
		}

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
			if(GetHP()+furia>=100){
				furia += GetHP() - 100;
				SetHP(100);
			}else{
				Damage(-furia, associated);
				furia=0;
			}
		}

		if (speed.x < 0) {
			associated.flipHorizontal = true;
		} else if (speed.x > 0) {
			associated.flipHorizontal = false;
		}

		if (speed.y == 0 && inputManager.IsKeyDown('w')) {
			speed.y = 1000;
		}
	}

	speed.x = dir * CHARACTER_SPEED;
	associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);

	if(inputManager.IsKeyDown('s') && !blocking){
		associated.box.y = 490;
	} else	if (associated.box.y > FLOOR_HEIGHT + associated.offsetHeight) {
		speed.y = 0;
		associated.box.y = FLOOR_HEIGHT + associated.offsetHeight;
	}

	if (characterState == ATTACK) {
		if (NORMAL_ATTACK_HIT_FRAME_START <= currentTime && NORMAL_ATTACK_HIT_FRAME_END > currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.3, 0.4});
			colliders->GetCollider("weapon")->SetOffset({90, 40});
			colliders->GetCollider("weapon")->Enable();
		} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	} else if (characterState == JUMP_ATTACK) {
		if (JUMP_ATTACK_HIT_FRAME_START <= currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.3, 0.4});
			colliders->GetCollider("weapon")->SetOffset({60, -25});
			colliders->GetCollider("weapon")->Enable();
		} else if (JUMP_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	} else	if (characterState == CROUCH_ATTACK) {
		if (CROUCH_ATTACK_HIT_FRAME_START <= currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.25, 0.35});
			colliders->GetCollider("weapon")->SetOffset({130, 0});
			colliders->GetCollider("weapon")->Enable();
		} else if (CROUCH_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	}

	if (!attacking) {
		if (GetHP() <= 0) {
			ChangeState(DEAD);
		} else if (associated.box.y > FLOOR_HEIGHT + associated.offsetHeight) {
			ChangeState(attackIssued ? CROUCH_ATTACK : CROUCH);
  	} else if(blocking){
			ChangeState(BLOCK);
		} else if(associated.box.y < FLOOR_HEIGHT + associated.offsetHeight){
			ChangeState(attackIssued ? JUMP_ATTACK : JUMP);
		} else if(dir != 0){
			ChangeState(attackIssued ? ATTACK : WALK);
		} else if(speed.x == 0 && speed.y==0){
			ChangeState(attackIssued ? ATTACK : IDLE);
		}
		if (attackIssued) {
			attacking = true;
		}
	}

	if(associated.box.x >= 512 + Camera::pos.x/2 && speed.x > 0)
		Camera::Follow(&associated);
	if(associated.box.x < 512 + Camera::pos.x && speed.x <0)
		Camera::Follow(&associated);

	if(associated.box.x >= Bloqueiotela.y  && Camera::IsFollowing()){
		Camera::Unfollow();
		if(associated.box.x >= Bloqueiotela.y + 512){
			associated.box.x = Bloqueiotela.y+ 512;
		}
	}
	else if(associated.box.x < Bloqueiotela.x + 512){
		Camera::Unfollow();
		if(associated.box.x < Bloqueiotela.x){
			associated.box.x = Bloqueiotela.x;
		}
	}

	if (stateChanged) {
		StateLogic();
		animationTimer.Restart();
	}
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter" || type == "Damageable";
}
void MainCharacter::ChangeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}

void MainCharacter::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* collider = colliders->GetCollider(idCollider).get();
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		if (idCollider == "body" && idOtherCollider == "body") {
			float offsetX = abs(associated.box.x - collider->box.x);
			if(collider->box.x + collider->box.w/2 > otherCollider->box.x + otherCollider->box.w / 2){
				associated.box.x = otherCollider->box.x + otherCollider->box.w - offsetX + 1;
			}
			else{
				associated.box.x = otherCollider->box.x - collider->box.w - offsetX - 1;
			}
		}
		if (idCollider == "weapon" && idOtherCollider == "body") {
			Component* damageable = other.GetComponent("Damageable");
			if (damageable != nullptr) {
				if (characterState == ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(NORMAL_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
				if (characterState == JUMP_ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(JUMP_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
				if (characterState == CROUCH_ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(CROUCH_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
			}
		}
	}
}

void MainCharacter::NotifyAnimationEnd () {
	if (attacking) {
		attacking = false;
		colliders->GetCollider("weapon")->Disable();
		ENEMY_HIT = false;
	}
	animationTimer.Restart();
}

void MainCharacter::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/HERO_IDLE.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
	}else if(characterState == JUMP && stateChanged){
		spr->Open("assets/img/HERO_JUMP.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/HERO_WALK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
	}else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/HERO_HURT.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(-15);
	}else if(characterState == CROUCH && stateChanged){
		spr->Open("assets/img/GenericCROUCH.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
	}else if(characterState == ATTACK && stateChanged){
		spr->Open("assets/img/HERO_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(-43);
	}else if(characterState == JUMP_ATTACK && stateChanged){
		spr->Open("assets/img/HERO_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(-43);
	}else if(characterState == CROUCH_ATTACK && stateChanged){
		spr->Open("assets/img/HERO_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(-43);
	}else if(characterState == DEAD && stateChanged){
		GameObject* go = new GameObject();
		go->box.x = associated.box.x - 100;
		go->box.y = associated.box.y - 10;
		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/HERO_DIE.png", 7, 0.2, 1.4));
		go->flipHorizontal = associated.flipHorizontal;

		Camera::Unfollow();
		associated.RequestDelete();
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}
Vec2 MainCharacter::GetCharacterPosition(){
	return colliders->GetCollider("body")->box.GetCenter();
}

void MainCharacter::OnDamage (float damage, GameObject& source) {
	if (characterState == BLOCK) {
		SetHP(GetHP() + damage * BLOCK_REDUCTION);
	}
}
