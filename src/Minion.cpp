#include "Minion.h"
#include "Sprite.h"
#include <math.h>
#include "Game.h"
#include "Bullet.h"

#define MINION_ANGULAR_SPEED M_PI / 4

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
		float arcOffsetDeg) :
		Component(associated), arc(arcOffsetDeg), alienCenter(alienCenter) {
	Sprite* spr = new Sprite(associated, "assets/img/minion.png");
	associated.AddComponent(spr);
	float scale = (rand() % 50 + 100) / 100.0;
	spr->SetScale(scale, scale);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();

	Vec2 pos(200, 0);
	pos = pos.GetRotated(arc);

	auto go = alienCenter.lock();

	pos += go->box.GetCenter();
	associated.box.x = pos.x - associated.box.w / 2;
	associated.box.y = pos.y - associated.box.h / 2;

}

void Minion::Update (float dt) {

	Vec2 pos(200, 0);
	arc += MINION_ANGULAR_SPEED * dt;
	pos = pos.GetRotated(arc);
	auto go = alienCenter.lock();

	if (!go) {
		associated.RequestDelete();
	}
	else {
		pos += go->box.GetCenter();
		associated.box.x = pos.x - associated.box.w / 2;
		associated.box.y = pos.y - associated.box.h / 2;
		associated.angleDeg = 90 + arc * (180 / M_PI);
	}
}

void Minion::Render () {

}

bool Minion::Is (string type) const {
	return type == "Minion";
}

void Minion::Shoot (Vec2 target) {
	
	GameObject* go = new GameObject();
	float angle = target.GetAngle(associated.box.GetCenter());
	go->AddComponent(
			new Bullet(*go, angle, 300, 5, 600,
					"assets/img/minionbullet1.png"));
	go->box.x = associated.box.GetCenter().x - go->box.w / 2;
	go->box.y = associated.box.GetCenter().y - go->box.h / 2;
	Game::GetInstance().GetState().AddObject(go);

}
