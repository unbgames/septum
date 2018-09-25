#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "Resources.h"
#include <string>
#include "Game.h"
#include "SDL_include.h"

using std::string;

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

shared_ptr<SDL_Texture> Resources::GetImage (string file) {
	auto it = imageTable.find(file);

	if (it == imageTable.end()) {
		SDL_Texture* texture = IMG_LoadTexture(
				Game::GetInstance().GetRenderer(), file.c_str());
		if (texture == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		shared_ptr<SDL_Texture> shared(texture, [] (SDL_Texture *t) -> void {
			SDL_DestroyTexture(t);
		});
		imageTable[file] = shared;
		return shared;
	}
	else {
		return it->second;
	}
}

void Resources::ClearImages () {
	auto it = imageTable.begin();
	while (it != imageTable.end()) {
		if (it->second.unique()) {
			imageTable.erase(it++);
		}
		else {
			++it;
		}
	}
}

shared_ptr<Mix_Music> Resources::GetMusic (string file) {
	auto it = musicTable.find(file);

	if (it == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		shared_ptr<Mix_Music> shared(music, [] (Mix_Music *m) -> void {
			Mix_FreeMusic(m);
		});
		musicTable[file] = shared;
		return shared;
	}
	else {
		return it->second;
	}
}

void Resources::ClearMusics () {
	auto it = musicTable.begin();
	while (it != musicTable.end()) {
		if (it->second.unique()) {
			musicTable.erase(it++);
		}
		else {
			++it;
		}
	}
}

shared_ptr<Mix_Chunk> Resources::GetSound (string file) {
	auto it = soundTable.find(file);

	if (it == soundTable.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		shared_ptr<Mix_Chunk> shared(chunk, [] (Mix_Chunk *c) -> void {
			Mix_FreeChunk(c);
		});
		soundTable[file] = shared;
		return shared;
	}
	else {
		return it->second;
	}
}

void Resources::ClearSounds () {
	auto it = soundTable.begin();
	while (it != soundTable.end()) {
		if (it->second.unique()) {
			soundTable.erase(it++);
		}
		else {
			++it;
		}
	}
}

shared_ptr<TTF_Font> Resources::GetFont (string file, int fontSize) {
	auto it = fontTable.find(file + std::to_string(fontSize));

	if (it == fontTable.end()) {
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if (font == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		shared_ptr<TTF_Font> shared(font, [] (TTF_Font *f) -> void {
			TTF_CloseFont(f);
		});
		fontTable[file + std::to_string(fontSize)] = shared;
		return shared;
	}
	else {
		return it->second;
	}
}
void Resources::ClearFonts () {
	auto it = fontTable.begin();
	while (it != fontTable.end()) {
		if (it->second.unique()) {
			fontTable.erase(it++);
		}
		else {
			++it;
		}
	}
}
