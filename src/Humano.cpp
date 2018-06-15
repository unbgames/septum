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

//#define CHARACTER_SPEED 650
//#define GRAVITY 2500
//int ISBLOCKED = 0;

//Humano* Humano::Humano = nullptr;

Humano::Humano (GameObject& associated):Component(associated),characterState(IDLE),demon(false) {
	//Humano = this;
	hp = 100;
	furia = 100;
	spr = new Sprite(associated, "assets/img/Colectable_human.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	Colliders* colliders = new Colliders(associated);
	collisionbox = new Collider(associated,{0.25,0.3},{-20,0});
	colliders->AddCollider("body", collisionbox);
	associated.AddComponent(colliders);
}
Humano::~Humano () {
	//Humano = nullptr;

}

void Humano::Start () {
}
void Humano::Update (float dt) {
	collisionbox->Update(dt);
}
void Humano::Render () {

}

bool Humano::Is (string type) const {
	return type == "Humano";
}
void Humano::changeState(stateType state){
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
