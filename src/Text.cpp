#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Text.h"
#include "Resources.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"

Text::Text (GameObject& associated, string fontFile, int fontSize,
		TextStyle style, string text, SDL_Color color) :
		Component(associated),
		texture(nullptr), text(text), style(style), fontFile(fontFile), fontSize(
				fontSize), color(
				color) {
	RemakeTexture();
}
Text::~Text () {

	if (texture) {
		SDL_DestroyTexture(texture);
	}

}

void Text::Update (float dt) {

}

void Text::Render () {
	SDL_Rect dstRect, clipRect;
	dstRect.x = associated.box.x - Camera::pos.x;
	dstRect.y = associated.box.y - Camera::pos.y;
	clipRect.w = dstRect.w = width;
	clipRect.h = dstRect.h = height;

	clipRect.x = 0;
	clipRect.y = 0;

	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture,
			&clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Text::Is (string type) const {
	return type == "Text";
}

void Text::SetText (string text) {

	this->text = text;
	RemakeTexture();

}
void Text::SetColor (SDL_Color color) {

	this->color = color;
	RemakeTexture();

}
void Text::SetStyle (TextStyle style) {

	this->style = style;
	RemakeTexture();

}
void Text::SetFontFile (string fontFile) {

	this->fontFile = fontFile;
	RemakeTexture();

}
void Text::SetFontSize (int fontSize) {

	this->fontSize = fontSize;
	RemakeTexture();

}

void Text::RemakeTexture () {
	if (texture) {
		SDL_DestroyTexture(texture);
	}

	font = Resources::GetFont(fontFile, fontSize);

	if (!font) {
		throw std::runtime_error(SDL_GetError());
	}
	SDL_Surface* surface;
	switch (style) {
		case SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color,
					{
					.r = 0, .g = 0, .b = 0, .a = 255 });
			break;
		case BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
		default:
			break;
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),
			surface);

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	associated.box.w = width;
	associated.box.h = height;

	SDL_FreeSurface(surface);
}
