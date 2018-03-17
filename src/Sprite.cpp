#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Game.h"
#include <stdexcept>

Sprite::Sprite () {
	texture = nullptr;
}

Sprite::Sprite (const char* file) {
	texture = nullptr;
	Sprite::Open(file);
}

Sprite::~Sprite () {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open (const char* file) {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file);
	if (texture == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render (int x, int y) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w;
	dstRect.h = clipRect.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect,
			&dstRect);
}

int Sprite::GetHeight () {
	return height;
}

int Sprite::GetWidth () {
	return width;
}

bool Sprite::IsOpen () {
	return (texture != nullptr);
}
