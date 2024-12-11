#include "Game.h"
#include <iostream>

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps; //max time between frames

	Uint32 frameStart;
	int frameTime;
	
	game = new Game();

	game->init("InfoSec Card Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
	std::cout << "Game initialized!" << std::endl;

	while (game->running()) {
		
		//SDL_GetTicks() returns the amount of ticks since SDL was started, we are essentially 
		//marking when we started rendering a frame
		frameStart = SDL_GetTicks();


		game->handleEvents();
		game->update();
		game->render();

		//now that we have done all of the tasks in the frame, we can calculate how long it took in total

		frameTime = SDL_GetTicks() - frameStart;


		//check if we have spent less than the target time between frames
		if (frameDelay > frameTime) {
			//delay the remaining time in order to reach the target time between frames
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();

	return 0;
}