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
		Component(associated) {
	texture = nullptr;
}

Sprite::Sprite (GameObject& associated, string file) :
		Sprite(associated) {
	Open(file);
}

Sprite::~Sprite () {

}

void Sprite::Open (string file) {
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render (float x, float y) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w;
	dstRect.h = clipRect.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect,
			&dstRect);
}

void Sprite::Render () {
	Sprite::Render(associated.box.x - Camera::pos.x,
			associated.box.y - Camera::pos.y);
}

int Sprite::GetHeight () const {
	return height;
}

int Sprite::GetWidth () const {
	return width;
}

bool Sprite::IsOpen () const {
	return (texture != nullptr);
}

void Sprite::Update (float dt) {

}

bool Sprite::Is (string type) const {
	return type == "Sprite";
}
