#include "Sound.h"
#include <stdexcept>
#include "Resources.h"

using std::string;

Sound::Sound (GameObject& associated) :
		Component(associated) {
	chunk = nullptr;
}

Sound::Sound (GameObject& associated, string file) :
		Sound(associated) {
	Open(file);
}

Sound::~Sound () {
	Stop();
}

void Sound::Open (string file) {
	chunk = Resources::GetSound(file);
}

void Sound::Play (int times) {
	channel = Mix_PlayChannel(channel, chunk, times - 1);
}

void Sound::Stop () {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
	}
}

bool Sound::IsOpen () const {
	return (chunk != nullptr);
}

void Sound::Update (float dt) {

}

void Sound::Render () {

}

bool Sound::Is (string type) const {
	return type == "Sound";
}

int Sound::GetChannel () const {
	return channel;
}
