#include "Face.h"
#include "Sound.h"

Face::Face (GameObject& associated) :
		Component(associated) {
	hitpoints = 30;
}

void Face::Damage (int damage) {
	hitpoints -= damage;
	if (hitpoints <= 0) {
		associated.RequestDelete();
		((Sound*) associated.GetComponent("Sound"))->Play();
	}
}

void Face::Update (float dt) {

}

void Face::Render () {

}

bool Face::Is (string type) {
	return type == "Face";
}