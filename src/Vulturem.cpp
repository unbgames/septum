#include "Vulturem.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "MainCharacter.h"

using std::weak_ptr;

#define CHARACTER_SPEED 450
#define NORMAL_ATTACK_HIT_FRAME_START 0.100
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 15
#define ATTACK_CD 0.600

Vulturem::Vulturem (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, "assets/img/VulturemHurting.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{1,1},{0,0});
	colliders->AddCollider("body", collisionbox);
	Collider *bico = new Collider(associated, {0.25,0.3}, {-70,-80}, false);
	colliders->AddCollider("bico", bico);
	associated.AddComponent(colliders);
	characterState = WALK;
	stateChanged = true;
}
Vulturem::~Vulturem () {
}

void Vulturem::Start () {
}
void Vulturem::Update (float dt) {
	if (GetHP() <= 0) {
		associated.RequestDelete();
	}
	animationTimer.Update(dt);
	stateTimer.Update(dt);

	float currentTime = stateTimer.Get();

	if(characterState == IDLE){
		if(currentTime >= ATTACK_CD){
			ChangeState(WALK);
		}
	}else if(characterState == WALK){
		// Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		// Vec2 PositionNow = associated.box.GetCenter();
		// if(PositionNow.GetDistance(Destination) > AtackRange){
		// 	int dir;
		// 	if(PositionNow.x > Destination.x){
		// 		dir = -1;
		// 	}else if(PositionNow.x < Destination.x){
		// 		dir = 1;
		// 	}else{
		// 		dir = 0;
		// 	}
		// 	speed.x = dir * CHARACTER_SPEED;
		//
		// 	if (speed.x < 0) {
		// 		associated.flipHorizontal = true;
		// 	} else if (speed.x > 0) {
		// 		associated.flipHorizontal = false;
		// 	}
		// 	associated.box.x += (speed.x * dt);
		// } else {
		// 	ChangeState(ATTACK);
		// 	attacking = true;
		// }

	}else if(characterState == ATTACK){
		float currentAnimTime = animationTimer.Get();
		if(attacking){
			if (NORMAL_ATTACK_HIT_FRAME_START <= currentAnimTime && NORMAL_ATTACK_HIT_FRAME_END > currentAnimTime) {
				colliders->GetCollider("bico")->Enable();
			} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentAnimTime){
				colliders->GetCollider("bico")->Disable();
			}
		}else{
			ChangeState(IDLE);
		}
	}
	if (stateChanged) {
		StateLogic();
		animationTimer.Restart();
	}
}
void Vulturem::Render () {
}

bool Vulturem::Is (string type) const {
	return type == "Vulturem" || type == "Damageable";
}
void Vulturem::ChangeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}
void Vulturem::NotifyAnimationEnd () {
	if (attacking) {
		attacking = false;
		playerHit = false;
		colliders->GetCollider("bico")->Disable();
		stateTimer.Restart();
	}
	animationTimer.Restart();
}

void Vulturem::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* collider = colliders->GetCollider(idCollider).get();
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		if (idCollider == "bico" && idOtherCollider == "body") {
			Component* damageable = other.GetComponent("Damageable");
			if (damageable != nullptr) {
				if(!playerHit) {
					((Damageable*) damageable)->Damage(NORMAL_ATTACK_DAMAGE);
					playerHit = true;
				}
			}
		}
	}
}

void Vulturem::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/VulturemHurting.png");
		spr->SetFrameCount(7);
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/VulturemWalking.png");
		spr->SetFrameCount(7);
	}else if(characterState== ATTACK && stateChanged){
		spr->Open("assets/img/VulturemAttack.png");
		spr->SetFrameCount(7);
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}
