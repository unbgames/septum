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
#define NORMAL_ATTACK_HIT_FRAME_START 0.400
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 15
#define ATTACK_CD 0.600
#define ATTACK_RANGE 170

Vulturem::Vulturem (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, "assets/img/VULT_IDLE.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.4,0.85},{-25,10});
	colliders->AddCollider("body", collisionbox);
	Collider *bico = new Collider(associated, {0.25, 0.25}, {120, 65}, false);
	colliders->AddCollider("bico", bico);
	associated.AddComponent(colliders);
	characterState = IDLE;
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

	if (characterState == IDLE) {
		if (currentTime >= ATTACK_CD) {
			ChangeState(WALK);
		}
	} else if(characterState == WALK){
		Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		Vec2 PositionNow = associated.box.GetCenter();
		if(PositionNow.GetDistance(Destination) > ATTACK_RANGE){
			int dir;
			if(PositionNow.x > Destination.x){
				dir = -1;
			}else if(PositionNow.x < Destination.x){
				dir = 1;
			}else{
				dir = 0;
			}
			speed.x = dir * CHARACTER_SPEED;

			if (speed.x < 0) {
				associated.flipHorizontal = true;
			} else if (speed.x > 0) {
				associated.flipHorizontal = false;
			}
			associated.box.x += (speed.x * dt);
		} else {
			ChangeState(ATTACK);
			attacking = true;
		}
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
		spr->Open("assets/img/VULT_IDLE.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
		colliders->GetCollider("body")->SetScale({0.4,0.85});
		colliders->GetCollider("body")->SetOffset({-25,10});
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/VULT_WALK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(0);
		colliders->GetCollider("body")->SetScale({0.4,0.85});
		colliders->GetCollider("body")->SetOffset({-25,10});
	}else if(characterState == ATTACK && stateChanged){
		spr->Open("assets/img/VULT_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangeOffsetHeight(-103);
		colliders->GetCollider("body")->SetScale({0.3, 0.55});
		colliders->GetCollider("body")->SetOffset({0, 60});
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}
