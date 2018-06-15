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

Corvus::Corvus (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, "assets/img/Enemie_crow.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Colliders* colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.25,0.3},{-20,0});
	colliders->AddCollider("body", collisionbox);
	associated.AddComponent(colliders);
}
Corvus::~Corvus () {
}

void Corvus::Start () {
}
void Corvus::Update (float dt) {
	if (GetHP() <= 0) {
		associated.RequestDelete();
	}
	if(ESTADO == IDLE){
		//faz nada;
	}else if(ESTADO == WALK){
		Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		Vec2 PositionNow = {associated.box.x,associated.box.y};
		if(PositionNow.GetDistance(Destination) > AtackRange){
			if(inputManager.IsKeyDown('a')){
				dir = -1;
			}else if(inputManager.IsKeyDown('d')){
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

			if (speed.y == 0 && inputManager.KeyPress('w')) {
				speed.y = 1000;
			} else {
				speed.y -= GRAVITY * dt;
			}
		}

			associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);
		}
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
