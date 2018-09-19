#include "Game.h"

int main(int argc, char** ){
	// Program entry point.
	Game game;
	while(!game.GetWindow()->IsDone()){
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
}