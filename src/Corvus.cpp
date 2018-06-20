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

using std::weak_ptr;

#define CHARACTER_SPEED 500
#define NORMAL_ATTACK_HIT_FRAME_START 0.600
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 35
bool attacking = false;
bool PLAYER_HIT = false;

Corvus::Corvus (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, "assets/img/Enemie_crow.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.25,0.3},{-20,0});
	colliders->AddCollider("body", collisionbox);
	Collider *bico = new Collider(associated,{0.25,0.3},{-70,-80});
	colliders->AddCollider("bico", bico);
	associated.AddComponent(colliders);
	ESTADO= WALK;
	stateChanged = true;
}
Corvus::~Corvus () {
}

void Corvus::Start () {
}
void Corvus::Update (float dt) {
	if (GetHP() <= 0) {
		associated.RequestDelete();
	}
	animationTimer.Update(dt);
	float currentTime = animationTimer.Get();
	
	if(ESTADO == IDLE){
		if(stateChanged){
			spr->Open("assets/img/Enemie_crow.png");
			spr->SetFrameCount(1);
			stateChanged = false;
		}
		//faz nada;
	}else if(ESTADO == WALK){
		if(stateChanged){
			spr->Open("assets/img/Enemie_crow.png");
			spr->SetFrameCount(1);
			stateChanged = false;
		}
		Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		Vec2 PositionNow = {associated.box.x,associated.box.y};
		if(PositionNow.GetDistance(Destination) > AtackRange){
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
				associated.flipHorizontal = false;
			} else if (speed.x > 0) {
				associated.flipHorizontal = true;
			}
			associated.box.x += (speed.x * dt);

		}else{
			ESTADO = ATK;
			stateChanged = true;
			attacking = true;
		}
	}else if(ESTADO == ATK){
		if(stateChanged){
			spr->Open("assets/img/socao.png");
			spr->SetFrameCount(1);
			stateChanged = false;
		}
		/*int attackIssued = false;
		if (inputManager.KeyPress('k')) {
			attackIssued = true;
		}*/
		if(attacking){
			if (NORMAL_ATTACK_HIT_FRAME_START <= currentTime && NORMAL_ATTACK_HIT_FRAME_END > currentTime) {
				// colliders->GetCollider("bico")->SetScale({0.3, 0.4});
				// colliders->GetCollider("bico")->SetOffset({120, 40});
			} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentTime){
				// colliders->GetCollider("bico")->SetScale({0,0});
				// colliders->GetCollider("bico")->SetOffset({0,0});
				PLAYER_HIT = false;
			}
		}else{

		}
	}
	if (stateChanged) {
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
		// colliders->GetCollider("bico")->SetScale({0,0});
		// colliders->GetCollider("bico")->SetOffset({0,0});
		//ENEMY_HIT = false;
	}
	animationTimer.Restart();
}

void Corvus::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	printf("%s - %s\n", idCollider.c_str(),idOtherCollider.c_str());
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* collider = colliders->GetCollider(idCollider).get();
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		/*if (idCollider == "body" && idOtherCollider == "body") {
			float offsetX = abs(associated.box.x - collider->box.x);
			if(collider->box.x + collider->box.w/2 > otherCollider->box.x + otherCollider->box.w / 2){
				associated.box.x = otherCollider->box.x + otherCollider->box.w - offsetX + 1;
			}
			else{
				associated.box.x = otherCollider->box.x - collider->box.w - offsetX - 1;
			}
		}*/
		if (idCollider == "bico" && idOtherCollider == "body") {
			Component* damageable = other.GetComponent("Damageable");
			if (damageable != nullptr) {
				if(!PLAYER_HIT) {
					((Damageable*) damageable)->Damage(NORMAL_ATTACK_DAMAGE);
					PLAYER_HIT = true;
				}
			}
		}
		/*if (idCollider == 'body' && idOtherCollider == 'bico'){
			Component* damageable = associated.GetComponent("Damageable");
			if(damageable != nullptr){
					((Damageable*)damageable)->Damage(NORMAL_ATTACK_DAMAGE);
					//PLAYER_HIT = true;

			}
		}*/
	}
}