#include "MenuState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "MainCharacter.h"
#include "FirstStageState.h"
#include "config.h"

MenuState::MenuState () {
}
MenuState::~MenuState () {

}

void MenuState::LoadAssets () {
	GameObject *splashScreen = new GameObject();
	splashScreen->AddComponent(
			new Sprite(*splashScreen, ASSETS_PATH("/img/TitleScreen1.png") ));
	splashScreen->AddComponent(new CameraFollower(*splashScreen));
	AddObject(splashScreen);

	GameObject* help = new GameObject();
	help->AddComponent(new CameraFollower(*help, {20, 450}));
	Text *list = new Text(*help, ASSETS_PATH("/font/Call me maybe.ttf"),30,Text::BLENDED,
	"Q\t\t\t\t\t\t\tBlock\nW\t\t\t\t\t\tAttack\nE\t\t\t\t\t\t\tHeal\nR\t\t\t\t\t\t\tDemon Form\nArrows\tMove"
	,{255,255,255});
	help->AddComponent(list);
	AddObject(help);

	GameObject* pressStart = new GameObject();
	pressStart->AddComponent(new CameraFollower(*pressStart, {470, 670}));
	Text *startText = new Text(*pressStart, ASSETS_PATH("/font/Call me maybe.ttf"),30,Text::BLENDED,
	"PRESS SPACEBAR TO START"
	,{255,255,255});
	pressStart->AddComponent(startText);
	AddObject(pressStart);

}
void MenuState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if(inputManager.KeyPress(' ')){
		Game& game = Game::GetInstance();
		game.Push(new FirstStageState());
	}

	UpdateArray(dt);
	Camera::Update(dt);
}
void MenuState::Render () {
	RenderArray();
}

void MenuState::Start () {
	LoadAssets();
	StartArray();
	started = true;
}
void MenuState::Pause () {

}
void MenuState::Resume () {
	// Camera::pos = {0, 0};
}
