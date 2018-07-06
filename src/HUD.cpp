#include "HUD.h"
#include "Sprite.h"
#include "Collider.h"
#include "MainCharacter.h"
#include "Camera.h"

bool demonio = false;

HUD::HUD (GameObject& associated):Component(associated){
	fundo = new GameObject();
	fundo->box.x = 36;
	fundo->box.y = 36;
	Sfundo = new Sprite(*fundo,"assets/img/hudbot.png");
	fundo->AddComponent(Sfundo);

	frente = new GameObject();
	frente->box.x = 36;
	frente->box.y = 36;
	Sfrente = new Sprite(*frente,"assets/img/hudtop.png");
	frente->AddComponent(Sfrente);

	lifepoints = new GameObject();
	lifepoints->box.x = 124;
	lifepoints->box.y = 72;
	Slife = new Sprite(*lifepoints,"assets/img/life.png");
	lifepoints->AddComponent(Slife);
	//Slife->SetScale(8.65,0.04);

	face = new GameObject();
	face->box.x = 0;
	face->box.y = 30;
	Sface = new Sprite(*face,"assets/img/HUDface.png");
	Sface->SetScale(0.65, 0.65);
	face->AddComponent(Sface);

	furypoints = new GameObject();
	furypoints->box.x = 124;
	furypoints->box.y = 105;
	Sfury = new Sprite(*furypoints,"assets/img/rage.png");
	//Sfury->SetScale(9.65,0.085);
	furypoints->AddComponent(Sfury);

}
void HUD::Update (float dt) {
	if (MainCharacter::mainCharacter) {
		if(MainCharacter::mainCharacter->demon != demonio){
			demonio = MainCharacter::mainCharacter->demon;
			if(demonio)
			Sface->Open("assets/img/HUDdemon.png");
			else
			Sface->Open("assets/img/HUDface.png");
		}
		Slife->SetScale(0.01*MainCharacter::mainCharacter->GetHP(),1);
		Sfury->SetScale(0.01*MainCharacter::mainCharacter->furia,1);
	}
	fundo->box.x = 36 + Camera::pos.x;
	frente->box.x = 36 + Camera::pos.x;
	lifepoints->box.x = 124 + Camera::pos.x;
	face->box.x = 0 + Camera::pos.x;
	furypoints->box.x = 124 + Camera::pos.x;


}
void HUD::Render () {
	Sfundo->Render();
	Slife->Render();
	Sfury->Render();
	Sfrente->Render();

	Sface->Render();
}
bool HUD::Is (string type) const {
	return type == "HUD";
}
