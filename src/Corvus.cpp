#include "Corvus.h"
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
#include "Character.h"

using std::weak_ptr;

#define CHARACTER_SPEED 250
#define NORMAL_ATTACK_HIT_FRAME_START 0.400
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 15
#define ATTACK_CD 0.600
#define ATTACK_RANGE 170
#define ACQUISITION_RANGE 770

Corvus::Corvus (GameObject& associated):Damageable(associated, 100) {
	Character* crt = new Character(associated, Character::COMPUTER);
	associated.AddComponent(crt);
	spr = new Sprite(associated, "assets/img/CORV_IDLE.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.4,0.85},{-25,10});
	colliders->AddCollider("body", collisionbox);
	Collider *weapon = new Collider(associated, {0.25, 0.25}, {120, 65}, false);
	colliders->AddCollider("weapon", weapon);
	associated.AddComponent(colliders);
	characterState = IDLE;
}
Corvus::~Corvus () {

}

void Corvus::Start () {
}
void Corvus::Update (float dt) {
	animationTimer.Update(dt);
	stateTimer.Update(dt);

	float currentTime = stateTimer.Get();

	if (GetHP() <= 0) {
		ChangeState(DEAD);
		FirstStageState::enemycount--;
		FirstStageState::tempoRestante+=6;
		MainCharacter::mainCharacter->furia+=20;
	} else if (MainCharacter::mainCharacter) {
		Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		Vec2 PositionNow = GetCharacterPosition();

		float distance = PositionNow.GetDistance(Destination);
		if (distance >= ACQUISITION_RANGE) {
			ChangeState(IDLE);
		} else if (characterState == IDLE) {
			if (currentTime >= ATTACK_CD) {
				ChangeState(WALK);
			}
		} else if(characterState == WALK){

			if(distance > ATTACK_RANGE){
				int dir = 0;
				if(PositionNow.x > Destination.x){
					dir = -1;
				}else if(PositionNow.x < Destination.x){
					dir = 1;
				}
				speed.x = dir * CHARACTER_SPEED;

				if (speed.x < 0) {
					associated.Flip(true);
				} else if (speed.x > 0) {
					associated.Flip(false);
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
					colliders->GetCollider("weapon")->Enable();
				} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentAnimTime){
					colliders->GetCollider("weapon")->Disable();
				}
			}else{
				ChangeState(IDLE);
			}
		}
	} else {
		ChangeState(IDLE);
	}
	if (stateChanged) {
		StateLogic();
		animationTimer.Restart();
	}
}
void Corvus::Render () {
}

bool Corvus::Is (string type) const {
	return type == "Corvus" || type == "Damageable";
}
void Corvus::ChangeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}
void Corvus::NotifyAnimationEnd () {
	if (attacking) {
		attacking = false;
		playerHit = false;
		colliders->GetCollider("weapon")->Disable();
		stateTimer.Restart();
	}
	animationTimer.Restart();
}

void Corvus::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* collider = colliders->GetCollider(idCollider).get();
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		Component* damageable = other.GetComponent("Damageable");
		if (damageable != nullptr) {
			if (idCollider == "weapon" && idOtherCollider == "body") {
				Component* character = other.GetComponent("Character");
				bool shouldAttack = true;
				if (character != nullptr) {
					if (((Character*) character)->faction != Character::PLAYER) {
						shouldAttack = false;
					}
				}
				if(!playerHit && shouldAttack) {
					playerHit = true;
					((Damageable*) damageable)->Damage(NORMAL_ATTACK_DAMAGE, associated);
				}
			}
		}
	}
}

void Corvus::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/CORV_IDLE.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({0, 0});
		colliders->GetCollider("body")->SetScale({0.4,0.85});
		colliders->GetCollider("body")->SetOffset({-25,10});
	}	else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/CORV_WALK.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-15, 0}, 15);
		colliders->GetCollider("body")->SetScale({0.38, 0.81});
		colliders->GetCollider("body")->SetOffset({-19.5, 5});
	} else if(characterState == ATTACK && stateChanged){
		spr->Open("assets/img/CORV_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-50, -103}, 15);
		colliders->GetCollider("body")->SetScale({0.31, 0.59});
		colliders->GetCollider("body")->SetOffset({-18, 64});
	} else if(characterState == DEAD && stateChanged){
		associated.ChangePositionOffset({0, 0});
		GameObject* go = new GameObject();
		go->box.x = associated.box.x;
		go->box.y = associated.box.y;
		go->flipHorizontal = associated.flipHorizontal;
		go->ChangePositionOffset({-34, -12}, -85);
		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/CORV_DIE.png", 7, 0.2, 1.4));
		associated.RequestDelete();
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}

Vec2 Corvus::GetCharacterPosition(){
	return colliders->GetCollider("body")->box.GetCenter();
}
