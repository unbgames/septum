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

void Damageable::OnDamage (float damage, GameObject& source) {

}

void Damageable::Damage (float damage, GameObject& source) {
  hp -= damage;
  OnDamage(damage, source);
}
