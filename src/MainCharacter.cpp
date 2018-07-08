#include "MainCharacter.h"
#include "Character.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include <math.h>
#include "Collider.h"
#include "Colliders.h"
#include "State.h"
#include "Damageable.h"
#include "Camera.h"
#include "Sound.h"
#include "FirstStageState.h"
#include "Collision.h"

using std::weak_ptr;

#define CHARACTER_SPEED 650
#define GRAVITY 1900
#define NORMAL_ATTACK_HIT_FRAME_START 0.550
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 35

#define CROUCH_ATTACK_HIT_FRAME_START 0.600
#define CROUCH_ATTACK_HIT_FRAME_END 0.650
#define CROUCH_ATTACK_DAMAGE 100

#define JUMP_ATTACK_HIT_FRAME_START 0.300
#define JUMP_ATTACK_HIT_FRAME_END 0.350
#define JUMP_ATTACK_DAMAGE 50
#define FLOOR_HEIGHT 450

#define BLOCK_REDUCTION 0.75

bool ENEMY_HIT = false;
bool ENEMY_BLOCKED = false;

Vec2 Bloqueiotela = {0,1920};

MainCharacter* MainCharacter::mainCharacter = nullptr;

MainCharacter::MainCharacter (GameObject& associated) :
		Damageable(associated, 100),characterState(IDLE),demon(false) {
	mainCharacter = this;
	furia = 100;
	Character* crt = new Character(associated, Character::PLAYER);
	associated.AddComponent(crt);
	spr = new Sprite(associated, "assets/img/HERO_IDLE.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

	colliders = new Colliders(associated);
	Collider* collisionbox = new Collider(associated, {0.5,0.8}, {-55, 0});
	Collider* weaponCollider = new Collider(associated, {0,0}, {0, 0}, false);
	colliders->AddCollider("body", collisionbox);
	colliders->AddCollider("weapon", weaponCollider);
	associated.AddComponent(colliders);
}
MainCharacter::~MainCharacter () {
	mainCharacter = nullptr;
	Camera::Unfollow();
}

void MainCharacter::Start () {
}
void MainCharacter::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();
	animationTimer.Update(dt);
	float currentTime = animationTimer.Get();
	int dir = 0;
	int attackIssued = false;
	bool blocking = inputManager.IsKeyDown('j');
	bool crouching = inputManager.IsKeyDown('s');
	if (inputManager.KeyPress('k')) {
		attackIssued = true;
	}

	if (speed.y != 0) {
		speed.y -= GRAVITY * dt;
	}

	if (!blocking) {
		if(inputManager.IsKeyDown('a')){
			dir = -1;
		} else if(inputManager.IsKeyDown('d')){
			dir = 1;
		}

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
			if(GetHP()+furia>=100){
				furia += GetHP() - 100;
				SetHP(100);
			} else{
				Damage(-furia, associated);
				furia=0;
			}
		}

		if (speed.x < 0) {
			associated.Flip(true);
		} else if (speed.x > 0) {
			associated.Flip(false);
		}

		if (speed.y == 0 && inputManager.IsKeyDown('w')) {
			speed.y = 1000;
		}
	}

	float speedChange = crouching ? 0.5 : 1;

	speed.x = dir * CHARACTER_SPEED * speedChange;
	associated.box.y -= (speed.y * dt);
	associated.box.x += (speed.x * dt);

	if (associated.box.y > FLOOR_HEIGHT + associated.positionOffset.y) {
		speed.y = 0;
		associated.box.y = FLOOR_HEIGHT + associated.positionOffset.y;
	}

	if (characterState == ATTACK) {
		if (NORMAL_ATTACK_HIT_FRAME_START <= currentTime && NORMAL_ATTACK_HIT_FRAME_END > currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.3, 0.4});
			colliders->GetCollider("weapon")->SetOffset({90, 40});
			colliders->GetCollider("weapon")->Enable();
		} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	} else if (characterState == JUMP_ATTACK) {
		if (JUMP_ATTACK_HIT_FRAME_START <= currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.3, 0.4});
			colliders->GetCollider("weapon")->SetOffset({60, -25});
			colliders->GetCollider("weapon")->Enable();
		} else if (JUMP_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	} else	if (characterState == CROUCH_ATTACK) {
		if (CROUCH_ATTACK_HIT_FRAME_START <= currentTime) {
			colliders->GetCollider("weapon")->SetScale({0.4, 0.35});
			colliders->GetCollider("weapon")->SetOffset({75, 40});
			colliders->GetCollider("weapon")->Enable();
		} else if (CROUCH_ATTACK_HIT_FRAME_END <= currentTime){
			colliders->GetCollider("weapon")->Disable();
		}
	}

	if (!attacking) {
		if (GetHP() <= 0) {
			ChangeState(DEAD);
		} else if(blocking){
			if (crouching) {
				ChangeState(CROUCH_BLOCK);
			} else {
				ChangeState(BLOCK);
			}
		} else if(associated.box.y < FLOOR_HEIGHT + associated.positionOffset.y){
			ChangeState(attackIssued ? JUMP_ATTACK : JUMP);
		} else if(dir != 0){
			if (crouching) {
				ChangeState(attackIssued ? CROUCH_ATTACK : CROUCH_WALK);
			} else {
				ChangeState(attackIssued ? ATTACK : WALK);
			}
		} else if(speed.x == 0 && speed.y==0){
			if (crouching) {
				ChangeState(attackIssued ? CROUCH_ATTACK : CROUCH);
			} else {
				ChangeState(attackIssued ? ATTACK : IDLE);
			}
		}
		if (attackIssued) {
			attacking = true;
		}
	}

	Rect* bodyBox = &(colliders->GetCollider("body")->box);
	float screenReference = Game::GetInstance().GetWidth() / 2;

	if (bodyBox->GetCenter().x > Bloqueiotela.y - screenReference
	|| bodyBox->GetCenter().x < Bloqueiotela.x + screenReference) {
		// Unfollows the character if it is before the half of the screen and after the left limit
		// Or if is after the half of the screend and before the right limit
		if (Camera::IsFollowing()) {
			Camera::Unfollow();
		}
	} else if ((bodyBox->GetCenter().x >= screenReference + Camera::pos.x && speed.x > 0)
	|| (bodyBox->GetCenter().x < screenReference + Camera::pos.x && speed.x < 0)) {
		// Follows the character if it is after the half of the screen and walking forward
		// Or if is before the half of the screend and walking back
		Camera::Follow(bodyBox);
	}

	// Blocks movement to either limit of screen
	if(bodyBox->x + bodyBox->w > Bloqueiotela.y){
		associated.box.x = Bloqueiotela.y - (bodyBox->x + bodyBox->w) + associated.box.x;
	} else if(bodyBox->x < Bloqueiotela.x){
		associated.box.x = Bloqueiotela.x - bodyBox->x + associated.box.x;
	}

	if (stateChanged) {
		StateLogic();
		animationTimer.Restart();
	}
}
void MainCharacter::Render () {

}

bool MainCharacter::Is (string type) const {
	return type == "MainCharacter" || type == "Damageable";
}
void MainCharacter::ChangeState(stateType state){
	if(characterState != state){
		characterState = state;
		stateChanged = true;
	}
}

void MainCharacter::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
	Colliders* otherColliders = (Colliders*)(other.GetComponent("Colliders"));
	Collider* collider = colliders->GetCollider(idCollider).get();
	Collider* otherCollider = otherColliders->GetCollider(idOtherCollider).get();
	if (otherColliders != nullptr) {
		if (idCollider == "body" && idOtherCollider == "body") {
			float offsetX = abs(associated.box.x - collider->box.x);
			if(collider->box.x + collider->box.w/2 > otherCollider->box.x + otherCollider->box.w / 2){
				associated.box.x = otherCollider->box.x + otherCollider->box.w - offsetX + 1;
			}
			else{
				associated.box.x = otherCollider->box.x - collider->box.w - offsetX - 1;
			}
		}
		if (idCollider == "weapon" && idOtherCollider == "body") {
			Component* damageable = other.GetComponent("Damageable");
			if (damageable != nullptr) {
				if (characterState == ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(NORMAL_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
				if (characterState == JUMP_ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(JUMP_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
				if (characterState == CROUCH_ATTACK && !ENEMY_HIT) {
					((Damageable*) damageable)->Damage(CROUCH_ATTACK_DAMAGE, associated);
					ENEMY_HIT = true;
				}
			}
		}
	}
}

void MainCharacter::NotifyAnimationEnd () {
	if (attacking) {
		attacking = false;
		colliders->GetCollider("weapon")->Disable();
		ENEMY_HIT = false;
	}
	animationTimer.Restart();
}

void MainCharacter::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/HERO_IDLE.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({0, 0});
		colliders->GetCollider("body")->SetScale({0.5,0.8});
		colliders->GetCollider("body")->SetOffset({-55,0});
	} else if(characterState == JUMP && stateChanged){
		spr->Open("assets/img/HERO_JUMP.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-30, -40}, 30);
		colliders->GetCollider("body")->SetScale({0.45, 0.69});
		colliders->GetCollider("body")->SetOffset({-37.325, 0});
	} else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/HERO_WALK.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-7, -3}, 0);
		colliders->GetCollider("body")->SetScale({0.48, 0.78});
		colliders->GetCollider("body")->SetOffset({-54, 0});
	} else if(characterState == CROUCH_WALK && stateChanged){
		spr->Open("assets/img/HERO_WALK_CROUCH.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-15, 15}, 50);
		colliders->GetCollider("body")->SetScale({0.54, 0.78});
		colliders->GetCollider("body")->SetOffset({-31.5, 22.5});
	} else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/HERO_BLOCK.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({4, 2});
		colliders->GetCollider("body")->SetScale({0.61, 0.93});
		colliders->GetCollider("body")->SetOffset({-35.5, 15});
	} else if(characterState == CROUCH_BLOCK && stateChanged){
		spr->Open("assets/img/HERO_BLOCK_CROUCH.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({0, 12});
		colliders->GetCollider("body")->SetScale({0.62, 0.77});
		colliders->GetCollider("body")->SetOffset({-31.5, 25});
	} else if(characterState == CROUCH && stateChanged){
		spr->Open("assets/img/HERO_IDLE_CROUCH.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({0, 15});
		colliders->GetCollider("body")->SetScale({0.51, 0.65});
		colliders->GetCollider("body")->SetOffset({-53.5, 2.5});
	} else if(characterState == ATTACK || characterState == JUMP_ATTACK && stateChanged){
		spr->Open("assets/img/HERO_ATTACK.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({0, -43});
		colliders->GetCollider("body")->SetScale({0.48, 0.72});
		colliders->GetCollider("body")->SetOffset({-59.7, 29});
	} else if(characterState == CROUCH_ATTACK && stateChanged){
		spr->Open("assets/img/HERO_ATTACK_CROUCH.png");
		spr->SetFrameCount(7);
		associated.ChangePositionOffset({-15, -20});
		colliders->GetCollider("body")->SetScale({0.45, 0.65});
		colliders->GetCollider("body")->SetOffset({-55, 38});
	} else if(characterState == DEAD && stateChanged){
		GameObject* go = new GameObject();
		go->box.x = associated.box.x - 100;
		go->box.y = associated.box.y - 10;
		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/HERO_DIE.png", 7, 0.2, 1.4));
		go->flipHorizontal = associated.flipHorizontal;

		Camera::Unfollow();
		associated.RequestDelete();
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}
Vec2 MainCharacter::GetCharacterPosition(){
	return colliders->GetCollider("body")->box.GetCenter();
}

void MainCharacter::OnDamage (float damage, GameObject& source) {
	if (characterState == BLOCK || characterState == CROUCH_BLOCK) {
		SetHP(GetHP() + damage * BLOCK_REDUCTION);
	}
}
