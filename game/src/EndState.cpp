#include "MenuState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "FirstStageState.h"
#include "EndState.h"
#include "config.h"

EndState::EndState () {
}
EndState::~EndState () {

}

void EndState::LoadAssets () {
	GameObject *splashScreen = new GameObject();
	splashScreen->AddComponent(
			new Sprite(*splashScreen, ASSETS_PATH("/img/EndScreen1.png") ));
	splashScreen->AddComponent(new CameraFollower(*splashScreen));
	AddObject(splashScreen);
	GameObject* textao = new GameObject();
	textao->AddComponent(new CameraFollower(*textao, {470, 300}));
	char aux[60];
	sprintf(aux,"Voce durou %.1f segundos",FirstStageState::tempojogado);
	//remover o texto anterior
	Text *visortempo = new Text(*textao, ASSETS_PATH("/font/Call me maybe.ttf"),30,Text::SOLID,aux,{255,255,255});
	textao->AddComponent(visortempo);
	AddObject(textao);
}
void EndState::Update (float dt) {


	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if(inputManager.KeyPress(' ')){
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new FirstStageState());
	}

	UpdateArray(dt);
	Camera::Update(dt);
}
void EndState::Render () {
	RenderArray();
}

void EndState::Start () {
	LoadAssets();
	StartArray();
	started = true;
}
void EndState::Pause () {

}
void EndState::Resume () {
	// Camera::pos = {0, 0};
}
