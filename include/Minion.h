#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include <string>
#include <memory>

using std::string;
using std::weak_ptr;

class Minion: public Component {
	public:
		Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
				float arcOffsetDeg = 0);
		void Update (float);
		void Render ();
		bool Is (string type) const;
		void Shoot (Vec2 target);
	private:
		weak_ptr<GameObject> alienCenter;
		float arc;
};
