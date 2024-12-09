#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"

/*
	Step 1) Handle inputs
	Step 2) Update elements as needed
	Step 3) Render

*/

class Game {
public:
	Game();
	~Game();
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };

	static SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window* window;
};

#endif /* GAME_H */