#include <vector>
#include <algorithm>
#include <string>
#include "GameObject.h"

using std::vector;
using std::string;

GameObject::GameObject () {
	isDead = false;
}

GameObject::~GameObject () {
	vector<Component*>::iterator it = components.begin();
	for (int var = components.size(); var > 0; --var) {
		delete *(it + var);
	}
	components.clear();
}

void GameObject::Update (float dt) {
	for (Component*& c : components) {
		c->Update(dt);
	}
}

void GameObject::Render () {
	for (Component*& c : components) {
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
	components.push_back(cpt);
}

void GameObject::RemoveComponent (Component* cpt) {
	components.erase(std::remove(components.begin(), components.end(), cpt),
			components.end());
}

Component* GameObject::GetComponent (string type) const {
	auto it = std::find_if(components.begin(), components.end(),
			[&type](Component* const& cpt) {return cpt->Is(type);});

	if (it != components.end()) {
		return *it;
	}
	else {
		return nullptr;
	}
}
