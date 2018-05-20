#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

#define ALIEN_ROTATION -0.6
#define REST_COOLDOWN 1.3

int Alien::alienCount = 0;

Alien::Alien (GameObject& associated, int nMinions, float timeOffset) :
		Component(associated), speed(100, 100), hp(60), nMinions(nMinions), state(
				RESTING), timeOffset(timeOffset) {
	Sprite* spr = new Sprite(associated, "assets/img/alien.png");
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

	Collider* col = new Collider(associated);
	associated.AddComponent(col);

	alienCount++;
}

void Alien::Start () {
	for (int m = 0; m < nMinions; ++m) {
		float offset = 2 * M_PI * m / nMinions;
		GameObject* go = new GameObject();
		go->AddComponent(
				new Minion(*go,
						Game::GetInstance().GetCurrentState().GetObjectPtr(
								&associated), offset));
		minionArray.emplace_back(
				Game::GetInstance().GetCurrentState().AddObject(go));
	}
}

Alien::~Alien () {
	minionArray.clear();
	alienCount--;
}


void Alien::Update (float dt) {
	associated.angleDeg += ALIEN_ROTATION;
	InputManager& inputManager = InputManager::GetInstance();

	if (PenguinBody::player != nullptr) {
		if (state == RESTING) {
			restTimer.Update(dt);
			if (restTimer.Get() >= REST_COOLDOWN + timeOffset) {
				destination = PenguinBody::player->GetCenterPosition();
				state = MOVING;
			}
		}
		else if (state == MOVING) {
			if (destination.GetDistance(associated.box.GetCenter())
					> speed.GetLength() * dt) {
				Vec2 dir = (destination - associated.box.GetCenter()).GetUnit();
				Vec2 dirUnit = dir.GetUnit();
				dir.x *= speed.x * abs(dirUnit.x);
				dir.y *= speed.y * abs(dirUnit.y);

					associated.box.x += (dir.x * dt);
				associated.box.y += (dir.y * dt);
			}
			else {
				associated.box.x = destination.x - associated.box.w / 2;
				associated.box.y = destination.y - associated.box.h / 2;

					Vec2 playerLocation = PenguinBody::player->GetCenterPosition();

					shared_ptr<GameObject> attacker;
				float minDistance = HUGE_VALF;
				for (auto& it : minionArray) {
					float distance = it.lock()->box.GetCenter().GetDistance(
							playerLocation);
					if (distance < minDistance) {
						minDistance = distance;
						attacker = it.lock();
					}
				}
				Minion* minion = (Minion*) (attacker->GetComponent("Minion"));
				minion->Shoot(playerLocation);

					state = RESTING;
				restTimer.Restart();
			}
		}
	}
	if (hp <= 0) {
		GameObject* go = new GameObject();
		go->box.x = associated.box.x;
		go->box.y = associated.box.y;
		Game::GetInstance().GetCurrentState().AddObject(go);
		go->AddComponent(
				new Sprite(*go, "assets/img/aliendeath.png", 4, 0.3, 1.2));
		Sound* sound = new Sound(*go, "assets/audio/boom.wav");
		go->AddComponent(sound);

		sound->Play();

		associated.RequestDelete();
	}
}

void Alien::Render () {

}

bool Alien::Is (string type) const {
	return type == "Alien";
}

void Alien::NotifyCollision (GameObject& other) {
	Component* bullet = other.GetComponent("Bullet");
	if (bullet != nullptr) {
		if (!((Bullet*) bullet)->targetsPlayer) {
			hp -= ((Bullet*) bullet)->GetDamage();
		}
	}
}
