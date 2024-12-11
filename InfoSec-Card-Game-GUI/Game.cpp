#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Button.h"
#include "CardVector.h"
#include "DefenseCard.h"
#include <cmath>
#include <iostream>

Map* map;
Mouse* mouse;
Button* startButton;
CardVector* player1Active;
DefenseCard card1, card2, card3, card4;
Manager manager;
Entity& player1(manager.addEntity());
Entity& player2(manager.addEntity());
Entity& deck(manager.addEntity());

SDL_Renderer* Game::renderer = nullptr;
//set these static variables to default values
int Game::widthSegment = 0;
int Game::heightSegment = 0;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	Game::widthSegment = width / 10;
	Game::heightSegment = height / 10;
	TTF_Init();
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
	
	mouse = new Mouse();
	startButton = new Button();
	//this will be how we select which texture to use
	//a higher y value will select a different tile when sprite sheet is oriented correctly
	startButton->srcRect.y = 0;
	startButton->destRect.x = width / 2;
	startButton->destRect.y = height / 2;
	
	//ecs implementation
	player1.addComponent<PositionComponent>();
	player1.getComponent<PositionComponent>().setPos((int)(widthSegment * 4.5), heightSegment * 8);
	//!TODO implement player method to generate a texture to use for the healthbar 
	//! OR make health component
	player1.addComponent<SpriteComponent>(96, 96, "healthBar.png");
	player1.addComponent<PlayerInfoComponent>(250, 100, "John Pork");

	int deckWidth = 128;
	int deckHeight = 192;
	deck.addComponent<PositionComponent>(widthSegment * 1, heightSegment * 4.5 - (deckHeight / 2));
	deck.addComponent<SpriteComponent>(deckWidth, deckHeight, "card.png");

	player1Active = new CardVector(4, heightSegment * 10 - 288);
	card1.setTex("testHand.png");
	card2.setTex("testHand.png");
	card3.setTex("testHand.png");
	card4.setTex("testHand.png");
	player1Active->addCard(card1);
	player1Active->addCard(card2);
	player1Active->addCard(card3);
	player1Active->addCard(card4);

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

	manager.draw();
	player1Active->draw();
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