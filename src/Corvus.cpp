#include "Corvus.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Colliders.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "MainCharacter.h"

using std::weak_ptr;

#define CHARACTER_SPEED 500
bool attacking = false;

Corvus::Corvus (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, "assets/img/Enemie_crow.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Colliders* colliders = new Colliders(associated);
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
	if (stateChanged) {
		//StateLogic();
		animationTimer.Restart();
	}
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
			spr->SetFrameCount(3);
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
		}
	}else if(ESTADO == ATK){
		if(stateChanged){
			spr->Open("assets/img/socao.png");
			spr->SetFrameCount(1);
			stateChanged = false;
		}
		attacking = true;
	}
}
void Corvus::Render () {
}

bool Corvus::Is (string type) const {
	return type == "Humano" || type == "Damageable";
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
