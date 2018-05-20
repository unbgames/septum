#include "EndState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "CameraFollower.h"
#include "Text.h"
#include "GameData.h"


EndState::EndState () {
}
EndState::~EndState () {

}

void EndState::LoadAssets () {
	GameObject *endScreen = new GameObject();
	string screenfile =
			GameData::playerVictory ?
					"assets/img/win.jpg" : "assets/img/lose.jpg";
	endScreen->AddComponent(new Sprite(*endScreen, screenfile));
	endScreen->AddComponent(new CameraFollower(*endScreen));
	AddObject(endScreen);

	string audiofile =
			GameData::playerVictory ?
					"assets/audio/endStateWin.ogg" :
					"assets/audio/endStateLose.ogg";

	backgroundMusic.Open(audiofile);


}
void EndState::Update (float dt) {
	InputManager& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	if (inputManager.KeyPress(' ')) {
		Game::GetInstance().Push(new StageState());
	}

	UpdateArray(dt);
}
void EndState::Render () {
	RenderArray();
}

void EndState::Start () {
	LoadAssets();
	StartArray();
	backgroundMusic.Play();
	started = true;
}

void EndState::Pause () {

}
void EndState::Resume () {

}
