#include "Colliders.h"
#include "Collider.h"
#include "Collision.h"
#include "GameObject.h"
#include <math.h>

Colliders::Colliders (GameObject& associated) :
		Component(associated){

}

Colliders::~Colliders () {
  colliders.clear();
}

void Colliders::Update (float dt) {
	for (auto c : colliders) {
		c.second->Update(dt);
	}
}

void Colliders::Render () {
	for (auto c : colliders) {
		c.second->Render();
	}
}

shared_ptr<Collider> Colliders::GetCollider (string identifier) {

  auto it = colliders.find(identifier);

	if (it == colliders.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}

}
bool Colliders::AddCollider (string identifier, Collider* collider) {

  if (GetCollider(identifier) == nullptr) {
    shared_ptr<Collider> shared(collider);
    colliders[identifier] = shared;
    return true;
  }
  else {
    return false;
  }

}
void Colliders::CheckCollision (GameObject& other) {
  for (auto colA : colliders) {
		if (!colA.second->IsEnabled()) {
			continue;
		}
    Colliders* listOther = (Colliders*) (other.GetComponent("Colliders"));
		if (listOther != nullptr) {
			for (auto colB : listOther->colliders) {
				if (!colB.second->IsEnabled()) {
					continue;
				}
				if (Collision::IsColliding(colA.second->box,
						colB.second->box,
						associated.angleDeg * M_PI / 180,
						other.angleDeg * M_PI / 180)) {
					associated.NotifyCollision(other, colA.first, colB.first);
					other.NotifyCollision(associated, colB.first, colA.first);
				}
			}
		}
	}
}

bool Colliders::Is (string type) const {
	return type == "Colliders";
}
