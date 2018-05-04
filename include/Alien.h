#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <vector>
#include <memory>
#include <queue>

using std::vector;
using std::queue;
using std::weak_ptr;

class Alien: public Component {
	public:
		Alien (GameObject& associated, int nMinions);
		~Alien ();
		void Start ();
		void Update (float dt);
		void Render ();
		bool Is (string type) const;
	private:
		class Action {
			public:
				enum ActionType {
					MOVE, SHOOT
				};
				ActionType type;
				Vec2 pos;
				Action (ActionType type, float x, float y);
		};
		
		Vec2 speed;
		int hp;
		queue<Action> taskQueue;
		vector<weak_ptr<GameObject>> minionArray;

};
