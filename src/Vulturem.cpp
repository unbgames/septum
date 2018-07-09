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
#include "Character.h"
#include "Randomizer.h"

using std::weak_ptr;

#define CHARACTER_SPEED 450
#define NORMAL_ATTACK_HIT_FRAME_START 0.400
#define NORMAL_ATTACK_HIT_FRAME_END 0.650
#define NORMAL_ATTACK_DAMAGE 15
#define ATTACK_RANGE 200
#define ACQUISITION_RANGE 2000

#define BLOCK_REDUCTION 0.5
#define BLOCK_CD 2
#define BLOCK_THRESHOLD 15

#define MIN_BLOCK_DURATION -1
#define MAX_BLOCK_DURATION 4
#define MIN_ATTACK_DURATION -2
#define MAX_ATTACK_DURATION 3
#define MIN_RUN_DURATION -3
#define MAX_RUN_DURATION 4

std::uniform_real_distribution<> blockRandomizer;
std::uniform_real_distribution<> runRandomizer;
std::uniform_real_distribution<> attackRandomizer;

bool blockReady = true;
float stateDuration = 0;

Vulturem::Vulturem (GameObject& associated):Damageable(associated, 60) {
	Character* crt = new Character(associated, Character::COMPUTER);
	associated.AddComponent(crt);
	spr = new Sprite(associated, "assets/img/VULT_IDLE.png",7,0.08);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	colliders = new Colliders(associated);
	Collider* collisionbox = new Collider(associated,{0.4,0.85},{-25,10});
	colliders->AddCollider("body", collisionbox);
	Collider *weapon = new Collider(associated, {0.25, 0.25}, {120, 65}, false);
	colliders->AddCollider("weapon", weapon);
	associated.AddComponent(colliders);
	characterState = IDLE;

	effects = new SoundCollection(associated);
	effects->AddSound("attack", new Sound(associated,"assets/audio/hit1.wav"));
	effects->AddSound("block", new Sound(associated,"assets/audio/block1.wav"));
	associated.AddComponent(effects);

	blockRandomizer = Randomizer::CreateUniformGenerator(MIN_BLOCK_DURATION, MAX_BLOCK_DURATION);
	runRandomizer = Randomizer::CreateUniformGenerator(MIN_RUN_DURATION, MAX_RUN_DURATION);
	attackRandomizer = Randomizer::CreateUniformGenerator(MIN_ATTACK_DURATION, MAX_ATTACK_DURATION);
}
Vulturem::~Vulturem () {

}

void Vulturem::Start () {
}
void Vulturem::Update (float dt) {

	animationTimer.Update(dt);
	stateTimer.Update(dt);
	if (!blockReady) {
		blockTimer.Update(dt);
		if (blockTimer.Get() >= BLOCK_CD) {
			blockTimer.Restart();
			blockReady = true;
		}
	}

	float currentTime = stateTimer.Get();

	if (GetHP() <= 0) {
		ChangeState(DEAD);
		FirstStageState::enemycount--;
		FirstStageState::tempoRestante+=10;
		MainCharacter::mainCharacter->power += 15;
	} else if (MainCharacter::mainCharacter) {
		Vec2 Destination = MainCharacter::mainCharacter->GetCharacterPosition();
		Vec2 PositionNow = GetCharacterPosition();

		float distance = PositionNow.GetDistance(Destination);
		if (distance >= ACQUISITION_RANGE) {
			ChangeState(IDLE);
		} else if (characterState == IDLE) {
			ChangeState(WALK);
		} else if(characterState == WALK){

			if(distance >= ATTACK_RANGE){
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
				if (blockReady) {
					ChangeState(BLOCK);
				} else {
					ChangeState(RUN);
				}
			}
		}	else if (characterState == RUN) {
			if (stateTimer.Get() >= stateDuration || distance >= 3 * ATTACK_RANGE) {
				ChangeState(WALK);
			} else {
				int dir = 0;
				if(PositionNow.x < Destination.x){
					dir = -1;
				}else if(PositionNow.x > Destination.x){
					dir = 1;
				}
				speed.x = dir * CHARACTER_SPEED;

				if (speed.x < 0) {
					associated.Flip(false);
				} else if (speed.x > 0) {
					associated.Flip(true);
				}
				associated.box.x += (speed.x * dt);
			}
		} else if (distance >= ATTACK_RANGE && !attacking) {
			ChangeState(WALK);
		} else if (characterState == BLOCK) {
			if (!blockReady) {
				ChangeState(RUN);
			} else if (stateTimer.Get() >= stateDuration) {
				ChangeState(ATTACK);
				attacking = true;
			}
		} else if(characterState == ATTACK){
			float currentAnimTime = animationTimer.Get();
			if(attacking){
				if (NORMAL_ATTACK_HIT_FRAME_START <= currentAnimTime && NORMAL_ATTACK_HIT_FRAME_END > currentAnimTime) {
					colliders->GetCollider("weapon")->Enable();
				} else if (NORMAL_ATTACK_HIT_FRAME_END <= currentAnimTime){
					colliders->GetCollider("weapon")->Disable();
				}
			} else {
				if (stateTimer.Get() >= stateDuration) {
					ChangeState(RUN);
				}
			}
		}
	} else {
		ChangeState(IDLE);
	}
	if (stateChanged) {
		StateLogic();
		stateTimer.Restart();
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
		effects->GetSound("attack")->Play(1);
		colliders->GetCollider("weapon")->Disable();
	}
	animationTimer.Restart();
}

void Vulturem::NotifyCollision (GameObject& other, string idCollider, string idOtherCollider) {
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

void Vulturem::StateLogic () {
	if(characterState == IDLE && stateChanged){
		spr->Open("assets/img/VULT_IDLE.png");
		spr->SetFrameCount(7);
		associated.SetPositionOffset({0, 0});
		colliders->GetCollider("body")->SetScale({0.4,0.85});
		colliders->GetCollider("body")->SetOffset({-25,10});
	} else if(characterState == WALK && stateChanged){
		spr->Open("assets/img/VULT_WALK.png");
		spr->SetFrameCount(7);
		associated.SetPositionOffset({-18, 0}, 18);
		colliders->GetCollider("body")->SetScale({0.37,0.82});
		colliders->GetCollider("body")->SetOffset({-18,5.5});
	}else if(characterState == ATTACK && stateChanged){
		spr->Open("assets/img/VULT_ATTACK.png");
		spr->SetFrameCount(7);
		associated.SetPositionOffset({-50, -107}, 24);
		colliders->GetCollider("body")->SetScale({0.33, 0.57});
		colliders->GetCollider("body")->SetOffset({-10, 64});
		stateDuration = Randomizer::GenerateUniform(attackRandomizer);
	}else if(characterState == BLOCK && stateChanged){
		spr->Open("assets/img/VULT_BLOCK.png");
		spr->SetFrameCount(7);
		associated.SetPositionOffset({39, -19}, -15);
		colliders->GetCollider("body")->SetScale({0.5,0.79});
		colliders->GetCollider("body")->SetOffset({-33,21});
		stateDuration = Randomizer::GenerateUniform(blockRandomizer);
	}else if(characterState == RUN && stateChanged){
		spr->Open("assets/img/VULT_RUN.png");
		spr->SetFrameCount(7);
		associated.SetPositionOffset({-20, 0}, 20);
		colliders->GetCollider("body")->SetScale({0.35,0.74});
		colliders->GetCollider("body")->SetOffset({-29,-6});
		stateDuration = Randomizer::GenerateUniform(runRandomizer);
	}else if(characterState == DEAD && stateChanged){
		associated.SetPositionOffset({0, 0});
		GameObject* go = new GameObject();
		go->box.x = associated.box.x;
		go->box.y = associated.box.y;
		go->flipHorizontal = associated.flipHorizontal;

		go->SetPositionOffset({-25, -6}, -85);

		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/VULT_DIE.png", 7, 0.2, 1.4));

		associated.RequestDelete();
	}
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	stateChanged = false;
}

void Vulturem::OnDamage (float damage, GameObject& source) {
	if (characterState == BLOCK) {
		if (associated.flipHorizontal != source.flipHorizontal) {
			if (damage < BLOCK_THRESHOLD) {
				SetHP(GetHP() + damage * BLOCK_REDUCTION);
			} else {
				blockReady = false;
				SetHP(GetHP() + BLOCK_THRESHOLD * BLOCK_REDUCTION);
			}
			effects->GetSound("block")->Play(1);
		}
	}
}

Vec2 Vulturem::GetCharacterPosition(){
	return colliders->GetCollider("body")->box.GetCenter();
}
