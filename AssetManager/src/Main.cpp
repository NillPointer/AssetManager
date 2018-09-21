#include "Game.h"

int main(int argc, char** ){
	// Program entry point.
	Game game;
	while(!game.getWindow()->IsDone()){
		game.handleInput();
		game.update();
		game.render();
		game.restartClock();
	}
	ImGui::SFML::Shutdown();
}