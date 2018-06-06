#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
class HUD: public Component {
	public:
		
		HUD (GameObject& associated);
		
		void Update (float dt);
		void Render ();
		bool Is (string type) const;
	private:
		GameObject *fundo;
		GameObject *frente;
		GameObject *lifepoints;
		GameObject *furypoints;
		GameObject *face;
		Sprite *Sfundo;
		Sprite *Sfrente;
		Sprite *Slife;
		Sprite *Sfury;
		Sprite *Sface;
};
