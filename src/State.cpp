#include "State.h"

State::State () :
		popRequested(false), quitRequested(false), started(false) {

}

State::~State () {
	objectArray.clear();
}

weak_ptr<GameObject> State::AddObject (GameObject* go) {
	shared_ptr<GameObject> ptr(go);
	objectArray.push_back(ptr);
	if (started) {
		go->Start();
	}
	return weak_ptr<GameObject>(ptr);
}

weak_ptr<GameObject> State::GetObjectPtr (GameObject* go) {
	for (auto& it : objectArray) {
		if (it.get() == go) {
			return std::weak_ptr<GameObject>(it);
		}
	}

	return std::weak_ptr<GameObject>();
}

bool State::PopRequested () const {
	return popRequested;
}

bool State::QuitRequested () const {
	return quitRequested;
}

void State::StartArray () {
	for (int i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Start();
	}
}

void State::RenderArray () {
	for (auto& go : objectArray) {
		go->Render();
	}
}

void State::UpdateArray (float dt) {
	for (int i = 0; i < objectArray.size(); ++i) {
		objectArray[i]->Update(dt);
	}
}
