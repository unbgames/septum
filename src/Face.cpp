#include "Face.h"
#include "Sound.h"
Face::Face (GameObject& associated) :
		Component(associated) {
	hitpoints = 30;
}

void Face::Damage (int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		Sound* sound = (Sound*) associated.GetComponent("Sound");
		sound->Play();
		associated.RequestDelete();
	}
}

void Face::Update (float dt) {

}

void Face::Render () {

}

bool Face::Is (string type) const {
	return type == "Face";
}
