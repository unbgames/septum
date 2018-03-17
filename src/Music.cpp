#include "Music.h"
#include <stdexcept>

using std::string;

Music::Music () {
	music = nullptr;
}

Music::Music (string file) {
	music = nullptr;
	
	Open(file);
}

void Music::Play (int times) {
	Mix_PlayMusic(music, times);
}

void Music::Stop (int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open (string file) {
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}
}

Music::~Music () {
	Stop();
	Mix_FreeMusic(music);
	music = nullptr;
}
