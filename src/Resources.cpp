#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "Resources.h"
#include <string>
#include "Game.h"
#include"SDL_include.h"

using std::string;

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage (string file) {
	auto it = imageTable.find(file);

	if (it == imageTable.end()) {
		SDL_Texture* texture = IMG_LoadTexture(
				Game::GetInstance().GetRenderer(), file.c_str());
		if (texture == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		return imageTable.emplace(file, texture).first->second;
	}
	else {
		return it->second;
	}
}

void Resources::ClearImages () {
	for (auto pair : imageTable) {
		SDL_DestroyTexture(pair.second);
	}
	imageTable.clear();
}

Mix_Music* Resources::GetMusic (string file) {
	auto it = musicTable.find(file);

	if (it == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		return musicTable.emplace(file, music).first->second;
	}
	else {
		return it->second;
	}
}

void Resources::ClearMusics () {
	for (auto pair : musicTable) {
		Mix_FreeMusic(pair.second);
	}
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound (string file) {
	auto it = soundTable.find(file);

	if (it == soundTable.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
		return soundTable.emplace(file, chunk).first->second;
	}
	else {
		return it->second;
	}
}

void Resources::ClearSounds () {
	for (auto pair : soundTable) {
		Mix_FreeChunk(pair.second);
	}
	musicTable.clear();
}

