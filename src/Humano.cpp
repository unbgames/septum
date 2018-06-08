#include "Humano.h"
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
	collisionbox = new Collider(associated,{0.6,0.6});
	associated.AddComponent(collisionbox);
	MainCharacter::mainCharacter->colideCOM.push_back(collisionbox);
}
Humano::~Humano () {
	//Humano = nullptr;

}

void Humano::Start () {
}
void Humano::Update (float dt) {
	collisionbox->Update(dt);
	/*InputManager& inputManager = InputManager::GetInstance();
	int dir;
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

	if (associated.box.y > 350 + ISBLOCKED) {
		speed.y = 0;
		associated.box.y = 350+ISBLOCKED;
	}

	if(inputManager.IsKeyDown('s')){
  		changeState(CROUCH);
  		furia+=0.5;
  	}else if(inputManager.IsKeyDown('j')){
  		changeState(BLOCK);
	}
  	else if(associated.box.y < 350){
		changeState(JUMP);
	}else if(dir != 0){
		changeState(WALK);
	}else if(speed.x == 0 && speed.y==0){
		changeState(IDLE);
	}

	associated.box.x = associated.box.x > 1100 ? 1100 : associated.box.x < 0 ? 0 : associated.box.x;
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/GenericIDLE.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}else if(characterState == JUMP && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		spr->SetFrameCount(7);
		hp-=10;
		stateChanged = false;
	}else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/testewalk.png");
		spr->SetFrameCount(8);
		stateChanged = false;
		//printf("Andou!\n");
	}else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/GenericBLOCK.png");
		spr->SetFrameCount(7);
		stateChanged = false;
		//printf("Andou!\n");
	}else if(characterState== CROUCH && stateChanged){
		spr->Open("assets/img/GenericCROUCH.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}*/
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
