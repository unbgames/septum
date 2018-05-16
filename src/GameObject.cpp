#include <vector>
#include <algorithm>
#include <string>
#include "GameObject.h"

using std::vector;
using std::string;

GameObject::GameObject () {
	isDead = false;
	started = false;
}

GameObject::~GameObject () {
	components.clear();
}

void GameObject::Update (float dt) {
	for (auto& c : components) {
		c->Update(dt);
	}
}

void GameObject::Render () {
	for (auto& c : components) {
		c->Render();
	}
}

bool GameObject::IsDead () const {
	return isDead;
}

void GameObject::RequestDelete () {
	isDead = true;
}

void GameObject::AddComponent (Component* cpt) {
	if (started) {
		cpt->Start();
	}
	components.emplace_back(cpt);
}

void GameObject::RemoveComponent (Component* cpt) {
	auto it = std::find_if(components.begin(), components.end(),
			[&](unique_ptr<Component>& p) {
				return p.get() == cpt;
			});

	if (it != components.end()) {
		components.erase(it);
	}
}

void GameObject::Start () {
	for (auto& cpt : components) {
		cpt->Start();
	}
	started = true;
}

Component* GameObject::GetComponent (string type) const {
	auto it = std::find_if(components.begin(), components.end(),
			[&type](unique_ptr<Component> const& cpt) {return cpt->Is(type);});

	if (it != components.end()) {
		return it->get();
	}
	else {
		return nullptr;
	}
}

void GameObject::NotifyCollision (GameObject& other) {
	for (auto& cpt : components) {
		cpt->NotifyCollision(other);
	}
}
