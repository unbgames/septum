#include "SoundCollection.h"
#include "Sound.h"
#include "Collision.h"
#include "GameObject.h"
#include <math.h>

SoundCollection::SoundCollection (GameObject& associated) :
		Component(associated){

}

SoundCollection::~SoundCollection () {
  sounds.clear();
}

void SoundCollection::Update (float dt) {
	for (auto c : sounds) {
		c.second->Update(dt);
	}
}

void SoundCollection::Render () {
	for (auto c : sounds) {
		c.second->Render();
	}
}

shared_ptr<Sound> SoundCollection::GetSound (string identifier) {

  auto it = sounds.find(identifier);

	if (it == sounds.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}

}
bool SoundCollection::AddSound (string identifier, Sound* sound) {

  if (GetSound(identifier) == nullptr) {
    shared_ptr<Sound> shared(sound);
    sounds[identifier] = shared;
    return true;
  }
  else {
    return false;
  }

}
bool SoundCollection::Is (string type) const {
	return type == "SoundCollection";
}
