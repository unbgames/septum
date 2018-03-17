#include "Music.h"
#include <stdexcept>

Music::Music () {
	music = nullptr;
}

Music::Music (const char* file) {
	music = nullptr;
	
	Open(file);
}

void Music::Play (int times) {
	Mix_PlayMusic(music, times);
}

void Music::Stop (int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open (const char * file) {
	music = Mix_LoadMUS(file);
	if (music == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
}

Music::~Music () {
	Stop();
	Mix_FreeMusic(music);
	music = nullptr;
}
