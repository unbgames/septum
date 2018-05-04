#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet (GameObject& associated, float angle, float speed, int damage,
		float maxDistance, string sprite) :
		Component(associated), damage(damage), distanceLeft(maxDistance), speed(
				speed, 0) {
	Sprite* spr = new Sprite(associated, sprite);
	associated.AddComponent(spr);
	associated.box.h = spr->GetHeight();
	associated.box.w = spr->GetWidth();
	this->speed = this->speed.GetRotated(angle);

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
int Bullet::GetDamage () {
	return damage;
}

