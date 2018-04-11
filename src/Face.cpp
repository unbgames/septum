#include "Face.h"
#include "Sound.h"
Face::Face (GameObject& associated) :
		Component(associated) {
	hitpoints = 30;
}

void Face::Damage (int damage) {
	// So it can`t keep damaging after death
	if (hitpoints > 0) {
		hitpoints -= damage;
		if (hitpoints <= 0) {
			((Sound*) associated.GetComponent("Sound"))->Play();
		}
	}
}

void Face::Update (float dt) {
	int playing = Mix_Playing(
			((Sound*) associated.GetComponent("Sound"))->GetChannel());
	if (hitpoints <= 0 && !playing) {
		associated.RequestDelete();
	}
}

void Face::Render () {

}

bool Face::Is (string type) const {
	return type == "Face";
}
