#include "Minion.h"
#include "Sprite.h"
#include <math.h>

#define MINION_ANGULAR_SPEED M_PI / 4

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
		float arcOffsetDeg) :
		Component(associated), arc(arcOffsetDeg), alienCenter(alienCenter) {
	Sprite* spr = new Sprite(associated, "assets/img/minion.png");
	associated.AddComponent(spr);
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
	}
}

void Minion::Render () {

}

bool Minion::Is (string type) const {
	return type == "Minion";
}

void Minion::Shoot (Vec2 target) {

}
