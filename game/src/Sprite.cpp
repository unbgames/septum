#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.h"
#include "Game.h"
#include "Component.h"
#include "Camera.h"
#include <stdexcept>
#include "Resources.h"

using std::string;

Sprite::Sprite (GameObject& associated) :
		Component(associated), scale(1, 1) {
	texture = nullptr;
}

Sprite::Sprite (GameObject& associated, string file, int frameCount,
		float frameTime, float secondsToSelfDestruct) :
		Sprite(associated) {
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	Open(file);
}

Sprite::~Sprite () {

}

void Sprite::Open (string file) {
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	SetClip(0, 0, width / frameCount, height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render (float x, float y, bool loop) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w * scale.x;
	dstRect.h = clipRect.h * scale.y;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect,
			&dstRect, associated.angleDeg, nullptr, associated.flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	if (loop) {
		if (x != 0) {
			SDL_Rect dstRect2;
			if (x < 0) {
				dstRect2.x = dstRect.w + x;
			} else if (x > 0) {
				dstRect2.x = x - dstRect.w;
			}
			dstRect2.y = y;
			dstRect2.w = dstRect.w;
			dstRect2.h = dstRect.h;
			SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect,
				&dstRect2, associated.angleDeg, nullptr, associated.flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		}
	}
}

void Sprite::Render () {
	Sprite::Render(associated.box.x - Camera::pos.x,
			associated.box.y - Camera::pos.y);
}

int Sprite::GetHeight () const {
	return height * scale.y;
}

int Sprite::GetWidth () const {
	return (width * scale.x) / frameCount;
}

bool Sprite::IsOpen () const {
	return (texture != nullptr);
}

void Sprite::Update (float dt) {

	if (secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() >= secondsToSelfDestruct) {
			associated.RequestDelete();
		}
	}

	timeElapsed += dt;

	if (timeElapsed > frameTime) {
		if (currentFrame < frameCount - 1) {
			SetFrame(currentFrame + 1);
		}
		else {
			associated.NotifyAnimationEnd();
			SetFrame(0);
		}
	}

}

bool Sprite::Is (string type) const {
	return type == "Sprite";
}

void Sprite::SetScale (float scaleX, float scaleY) {
	scale.x = scaleX > 0 ? scaleX : 0.01;
	scale.y = scaleY > 0 ? scaleY : 0.01;

	/*Vec2 currentCenter = associated.box.GetCenter();

	associated.box.w = (width / frameCount) * scale.x;
	associated.box.h = height * scale.y;
	associated.box.x = currentCenter.x - associated.box.w / 2;
	associated.box.y = currentCenter.y - associated.box.h / 2;*/
}

Vec2 Sprite::GetScale () const {
	return scale;
}

void Sprite::SetFrame (int frame) {

	if (frame < 0 || frame >= frameCount) {
		frame = 0;
	}

	currentFrame = frame;

	SetClip(currentFrame * width / frameCount, clipRect.y, width / frameCount,
			height);

	timeElapsed = 0;

}
void Sprite::SetFrameCount (int frameCount) {

	this->frameCount = frameCount;
	SetScale(scale.x, scale.y);
	SetFrame(0);

}
void Sprite::SetFrameTime (float frameTime) {
	this->frameTime = frameTime;
}
