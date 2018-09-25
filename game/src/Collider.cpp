#include "Collider.h"
#include "GameObject.h"
#include <math.h>

#include "Camera.h"
#ifdef DEBUG
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider (GameObject& associated, Vec2 scale, Vec2 offset, bool enabled) :
		associated(associated), scale(scale), offset(offset), enabled(enabled) {

}

void Collider::Update (float dt) {

	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	Vec2 rotated = offset.GetRotated(associated.angleDeg * M_PI / 180);

	int flipped = associated.flipHorizontal ? -1 : 1;

	box.x = associated.box.GetCenter().x + (flipped * rotated.x) - box.w / 2;
	box.y = associated.box.GetCenter().y + rotated.y - box.h / 2;
}

void Collider::Render () {
#ifdef DEBUG
	if (enabled) {
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
	}
#endif // DEBUG
}

void Collider::SetScale (Vec2 scale) {
	this->scale = scale;
}

void Collider::Enable () {
	enabled = true;
}

void Collider::Disable () {
	enabled = false;
}

bool Collider::IsEnabled () {
	return enabled;
}

void Collider::SetOffset (Vec2 offset) {
	this->offset = offset;
}

Vec2 Collider::GetScale() const {
	return scale;
}
Vec2 Collider::GetOffset() const {
	return offset;
}
