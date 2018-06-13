#include "MainCharacter.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "State.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "Collision.h"

using std::weak_ptr;

#define CHARACTER_SPEED 650
#define GRAVITY 2500
int ISBLOCKED = 0;

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Component(associated),characterState(IDLE),demon(false) {
	mainCharacter = this;
	hp = 100;
	furia = 100;
	spr = new Sprite(associated, "assets/img/player_idle.png",1,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	collisionbox = new Collider(associated,{0.8,0.8});
	associated.AddComponent(collisionbox);
}
MainCharacter::~MainCharacter () {
	mainCharacter = nullptr;

}

void MainCharacter::Start () {
}
void MainCharacter::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	int dir;
	if (inputManager.KeyPress('k')) {
		attackIssued = true;
	}
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

	if (associated.box.y > 250 + ISBLOCKED) {
		speed.y = 0;
		associated.box.y = 250+ISBLOCKED;
	}
	collisionbox->Update(dt);
	float ofsetjump=CantWalk();
	if(ofsetjump){
			associated.box.x -= (speed.x * dt);
	}

	if(inputManager.IsKeyDown('s')){
  		changeState(attackIssued ? CROUCH_ATTACK : CROUCH);
  		furia+=0.5;
  	}else if(inputManager.IsKeyDown('j')){
  		changeState(BLOCK);
	}
  	else if(associated.box.y < 250){
		changeState(attackIssued ? JUMP_ATTACK : JUMP);
	}else if(dir != 0){
		changeState(attackIssued ? ATTACK : WALK);
	}else if(speed.x == 0 && speed.y==0){
		changeState(attackIssued ? ATTACK : IDLE);
	}

	associated.box.x = associated.box.x > 1100 ? 1100 : associated.box.x < 0 ? 0 : associated.box.x;
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/player_idle.png");
		spr->SetFrameCount(1);
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
	}else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/GenericBLOCK.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}else if(characterState== CROUCH && stateChanged){
		spr->Open("assets/img/GenericCROUCH.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}else if(characterState== ATTACK && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}else if(characterState== JUMP_ATTACK && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}else if(characterState== CROUCH_ATTACK && stateChanged){
		spr->Open("assets/img/GenericJUMP.png");
		spr->SetFrameCount(7);
		stateChanged = false;
	}
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter";
}
void MainCharacter::changeState(stateType state){
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
float MainCharacter::CantWalk(){
	//printf("Chamou CantWalk size:%d\n",colideCOM.size());
	for(int i=0;i<colideCOM.size();i++){
		//printf("Atual:%.0f,%.0f,Bloco:%.0f,%.0f\n",collisionbox->box.x,collisionbox->box.y,colideCOM[i]->box.x,colideCOM[i]->box.y);
		if(Collision::IsColliding(collisionbox->box, colideCOM[i]->box,0, 0)){
			if(characterState!=WALK){//3 é chute
				//problema pulando
				printf("Achou o bug no pulo\n");
				if(collisionbox->box.x+collisionbox->box.w/2>colideCOM[i]->box.x+colideCOM[i]->box.w/2)
					//passa
					associated.box.x = colideCOM[i]->box.x+colideCOM[i]->box.w;
				else{
					associated.box.x =(colideCOM[i]->box.x - associated.box.w);
				}
			}
			printf("COlidiu\n");
			return 1;
		}
	}
	return 0;
}

void MainCharacter::NotifyAnimationEnd () {
	if (attackIssued) {
		attackIssued = false;
	}
}
