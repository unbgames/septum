#include "Bullet.h"
#include "Sprite.h"
#include <math.h>
#include "Collider.h"

Bullet::Bullet (GameObject& associated, float angle, float speed, int damage,
		float maxDistance, string sprite, bool targetsPlayer, int frameCount,
		float frameTime) :
		Component(associated), speed(speed, 0), distanceLeft(maxDistance), damage(
				damage), targetsPlayer(targetsPlayer) {
	Sprite* spr = new Sprite(associated, sprite, frameCount, frameTime);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	associated.angleDeg = (180 / M_PI) * angle;
	this->speed = this->speed.GetRotated(angle);

	Collider* col = new Collider(associated);
	associated.AddComponent(col);

}
void Bullet::Update (float dt) {

	Vec2 dir(1, 1);

	dir.x *= speed.x * dt;
	dir.y *= speed.y * dt;

	associated.box.x += dir.x;
	associated.box.y += dir.y;

	distanceLeft -= dir.GetLength();

	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}

}
void Bullet::Render () {

}
bool Bullet::Is (string type) const {
	return type == "Bullet";
}
int Bullet::GetDamage () const {
	return damage;
}

void Bullet::NotifyCollision (GameObject& other) {
	if ((other.GetComponent("Alien") && !targetsPlayer)
			|| (other.GetComponent("PenguinBody") && targetsPlayer)) {
		associated.RequestDelete();
	}
}
