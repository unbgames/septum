#include "Character.h"
#include "GameObject.h"

Character::Character (GameObject& associated, factionType faction) :
		Component(associated), faction(faction) {

}

void Character::Update (float dt) {

}

bool Character::Is (string type) const {
	return type == "Character";
}

void Character::Render () {

}
