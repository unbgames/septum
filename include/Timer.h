#pragma once
class Timer {
	public:
		Timer ();

		Timer (float time);

		void Update (float dt);
		void Restart ();
		float Get ();
	private:
		float time;
};
