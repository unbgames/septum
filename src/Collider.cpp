#include "Collider.h"
#include "GameObject.h"
#include <math.h>

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider (GameObject& associated, Vec2 scale, Vec2 offset) :
		Component(associated), scale(scale), offset(offset) {
	
}

void Collider::Update (float dt) {
	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	Vec2 rotated = offset.GetRotated(associated.angleDeg * M_PI / 180);

	box.x = associated.box.GetCenter().x + rotated.x - box.w / 2;
	box.y = associated.box.GetCenter().y + rotated.y - box.h / 2;

}

void Collider::Render () {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(
			associated.angleDeg / (180 / M_PI))
	+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg/(180/M_PI) )
	+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) )
	+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/M_PI) )
	+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is (string type) const {
	return type == "Collider";
}

void Collider::SetScale (Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset (Vec2 offset) {
	this->offset = offset;
}
