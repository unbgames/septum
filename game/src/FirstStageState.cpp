#include "FirstStageState.h"
#include "Sprite.h"
#include "Background.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "HUD.h"
#include "Humano.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Colliders.h"
#include "Corvus.h"
#include "Vulturem.h"
#include "EndState.h"
#include "stdio.h"
#include "stdlib.h"
#include "config.h"


float A,B;
float FirstStageState::tempoRestante(20);
float FirstStageState::tempojogado(0);
int FirstStageState::enemycount(2);

FirstStageState::FirstStageState () {
}
FirstStageState::~FirstStageState () {

}

void FirstStageState::LoadAssets () {
	music.Open("assets/audio/theme.wav");

	GameObject *background = new GameObject();
	Background* bg = new Background(*background, 0.03);
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/sky.png") ));
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/clouds_1.png") ));
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/rocks.png") ));
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/clouds_2.png") ));
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/rocks_1.png") ));
	bg->AddLayer(new Sprite(*background, ASSETS_PATH("/img/rocks_2.png") ));
	background->AddComponent(bg);
	AddObject(background);

	GameObject *map = new GameObject();
	map->box.y = 60;
	map->AddComponent(
			new TileMap(*map, ASSETS_PATH("/map/tileMap.txt"),
				new TileSet(256, 128, ASSETS_PATH("/img/teste tile1.png"), *map),{0,-75}));
	AddObject(map);

	GameObject *character = new GameObject();
	character->AddComponent(
			new MainCharacter(*character));
	character->box.y = 450;
	AddObject(character);

	GameObject *Hud = new GameObject();
	Hud->AddComponent(new HUD(*Hud));
	AddObject(Hud);

	GameObject *corvo = new GameObject();
	corvo->box.x = 800;
	corvo->box.y = 450;
	corvo->AddComponent(new Corvus(*corvo));

	AddObject(corvo);
	GameObject *urubu = new GameObject();
	urubu->box.x = 1100;
	urubu->box.y = 450;
	urubu->AddComponent(new Vulturem(*urubu));
	AddObject(urubu);

	cronometro = new GameObject();
	AddObject(cronometro);

}
void FirstStageState::Update (float dt) {
	tempoJOGO.Update(dt);
	char aux[60];
	sprintf(aux,"%.1f I %.1f",tempoJOGO.Get(),tempoRestante);
	//remover o texto anterior
	Component* textanterior = cronometro->GetComponent("Text");
	if(textanterior != nullptr)
		((Text*)textanterior)->SetText(aux);
	else{
		Text *visortempo = new Text(*cronometro, ASSETS_PATH("/font/Call me maybe.ttf"),30,Text::SOLID,aux,{0,0,0});
		cronometro->AddComponent(visortempo);
	}
	tempojogado = tempoJOGO.Get();
	if(tempojogado >= tempoRestante || MainCharacter::mainCharacter == nullptr || MainCharacter::mainCharacter->GetHP() <= 0){
		//condicao de termino
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new EndState());
	}
	Camera::Update(dt);

	if (!popRequested) {
		A = rand()%10000;//esse valor eh meio que a taxa de spawn dos inimigos
		if(A < tempojogado || enemycount == 0 && enemycount < 6){
			B = rand()%100;
			if(B<tempojogado){
				GameObject *forte = new GameObject();
				forte->box.x = MainCharacter::mainCharacter->GetCharacterPosition().x + rand()%1000;
				forte->box.y = 450;
				forte->AddComponent(new Vulturem(*forte));
				AddObject(forte);
				//spawna forte
			}else{
				//spawna fraco
				GameObject *fraco = new GameObject();
				fraco->box.x = MainCharacter::mainCharacter->GetCharacterPosition().x + rand()%1000;
				fraco->box.y = 450;
				fraco->AddComponent(new Corvus(*fraco));
				AddObject(fraco);
			}
			enemycount++;
		}
	}

	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	for (int i = 0; i < objectArray.size(); ++i) {
		Component* cptA = objectArray[i]->GetComponent("Colliders");
		if (cptA != nullptr) {
			for (int j = i + 1; j < objectArray.size(); ++j) {
				Component* cptB = objectArray[j]->GetComponent("Colliders");
				if (cptB != nullptr) {
					((Colliders*) cptA)->CheckCollision(*objectArray[j].get());
				}
			}
		}
	}
	UpdateArray(dt);

	vector<shared_ptr<GameObject>>::iterator it = objectArray.begin();
	for (int i = objectArray.size() - 1; i >= 0; --i) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(it + i);
		}
	}
	quitRequested = inputManager.QuitRequested();
	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	cronometro->box.y = Camera::pos.y + 20;
	cronometro->box.x = Camera::pos.x + 300;
}
void FirstStageState::Render () {
	RenderArray();
	//map.Render();
}

void FirstStageState::Start () {
	Camera::Unfollow();
	Camera::pos = {0, 0};
	tempoRestante = 20;
	tempojogado = 0;
	enemycount = 2;
	LoadAssets();
	StartArray();
	music.Play();
	started = true;
}
void FirstStageState::Pause () {

}
void FirstStageState::Resume () {
}
