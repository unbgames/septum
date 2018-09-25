#include "Humano.h"
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

Humano::Humano (GameObject& associated):Damageable(associated, 100) {
	spr = new Sprite(associated, ASSETS_PATH("/img/Colectable_human.png"),1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Colliders* colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.25,0.3},{-20,0});
	colliders->AddCollider("body", collisionbox);
	associated.AddComponent(colliders);
}
Humano::~Humano () {
}

void Humano::Start () {
}
void Humano::Update (float dt) {
	if (GetHP() <= 0) {
		associated.RequestDelete();
	}
}
void Humano::Render () {
}

bool Humano::Is (string type) const {
	return type == "Humano" || type == "Damageable";
}
void Humano::ChangeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}
