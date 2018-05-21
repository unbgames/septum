#include "Game.h"
#include "FirstStageState.h"
int main (int argc, char** argv) {
	Game& game = Game::GetInstance();
	game.Push(new FirstStageState());
	game.Run();
}
