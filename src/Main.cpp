#include "Game.h"
int main (int argc, char** argv) {
	Game game = Game::GetInstance().Run();
	game.Run();
}
