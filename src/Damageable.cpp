#include "Damageable.h"

Damageable::Damageable (GameObject& associated, float hp) : Component(associated), hp(hp){

}

Damageable::~Damageable () {

}

float Damageable::GetHP () const {
  return hp;
}

void Damageable::SetHP (float hp) {
  this->hp = hp;
}

void Damageable::Damage (float damage) {
  hp -= damage;
  if (hp < 0) {
    hp = 0;
  }
}
