#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Button.h"
#include <iostream>
 
Map* map;
Mouse* mouse;
Button* startButton;

SDL_Renderer* Game::renderer = nullptr; 

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	/*SDL_Surface* tmpSurface = IMG_Load("wifi.png");
	cardTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);*/
	//Replaced the above with the following function
	map = new Map();
	mouse = new Mouse();
	startButton = new Button();
	//this will be how we select which texture to use
	//a higher y value will select a different tile when sprite sheet is oriented correctly
	startButton->srcRect.y = 0;
	startButton->destRect.x = width / 2;
	startButton->destRect.y = height / 2;
	
	//ecs implementation
	newPlayer.addComponent<PositionComponent>(100, 500);
	newPlayer.getComponent<PositionComponent>().setPos(150, 150);
	newPlayer.addComponent<SpriteComponent>("wifi.png");

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (startButton->isSelected) {
				std::cout << "Start button clicked!" << std::endl;
			}
		}
	default:
		break;
	}
}
void Game::update() {
	/*
	Not planning on actually updating things directly here, 
	but calling the update() functions of other objects
	*/
	manager.refresh();
	startButton->update(*mouse);
	mouse->update();
	manager.update();

	/*if (newPlayer.getComponent<PositionComponent>().x() > 100) {
		newPlayer.getComponent<SpriteComponent>().setTex("water.png");
	}*/
}
void Game::render() {
	SDL_RenderClear(renderer);
	//this is where we would add stuff to render
	//the first null expects the source rectange (what you want to draw)
	//and the second expects where  you want to draw it to. 
	//using null for both of these just puts the whole image on the whole screen :)

	map->drawMap();
	manager.draw();
	startButton->draw();
	//draw the mouse last so it's on top of everything!
	mouse->draw();
	SDL_RenderPresent(renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}