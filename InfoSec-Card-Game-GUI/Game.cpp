#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Button.h"
#include "CardVector.h"
#include <cmath>
#include <iostream>

enum InteractionState {
	Idle,
	SelectingCard,
	SelectingTarget
};
InteractionState currentState = Idle;

Map* map;
Mouse* mouse;
Button* startButton;
CardVector* player1Hand;
CardVector* player2Hand;
CardVector* player1Active;
CardVector* player2Active;
Card card1, card2, card3, card4;
Card card5, card6, card7, card8;
Manager manager;
Entity& player1(manager.addEntity());
Entity& player2(manager.addEntity());
Entity& deck(manager.addEntity());

Button* selectedCardButton;
int selectedCardIndex;
CardVector* selectedCardVector;
bool mouseClicked = false;
bool actionQueued = false;

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

	//!TODO rearrange this!
	player2.addComponent<PositionComponent>(widthSegment * 4.5, heightSegment * .5);
	player2.addComponent<SpriteComponent>(96, 96, "healthBar.png");
	player2.addComponent<PlayerInfoComponent>(250, 100, "Hawk 2... uhhhhh");

	int deckWidth = 128;
	int deckHeight = 192;
	deck.addComponent<PositionComponent>(widthSegment * 1, heightSegment * 4.5 - (deckHeight / 2));
	deck.addComponent<SpriteComponent>(deckWidth, deckHeight, "card.png");

	player1Hand = new CardVector(4, heightSegment * 10 - 288);
	player1Hand->setX(widthSegment / 2);

	player2Hand = new CardVector(4, heightSegment * 0);
	player2Hand->setX(widthSegment / 2);

	player1Active = new CardVector(6, heightSegment * 7.25 - 288);
	player1Active->setX(widthSegment * 3.25);

	player2Active = new CardVector(6, heightSegment * 2.5);
	player2Active->setX(widthSegment * 3.25);

	card1.setTex("testHand.png");
	card2.setTex("card.png");
	card3.setTex("testHand.png");
	card4.setTex("testHand.png");
	player1Hand->addCard(card1);
	player1Hand->addCard(card2);
	player1Hand->addCard(card3);
	player1Hand->addCard(card4);
	player2Hand->addCard(card1);
	player2Hand->addCard(card2);
	player2Hand->addCard(card3);
	player2Hand->addCard(card4);
	player1Active->addCard(card1);
	player1Active->addCard(card2);
	player1Active->addCard(card3);
	player1Active->addCard(card4);
	player2Active->addCard(card1);
	player2Active->addCard(card2);
	player2Active->addCard(card3);
	player2Active->addCard(card4);

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (mouseClicked) {
				break;
			}
			if (startButton->isSelected) {
				std::cout << "Start button clicked!" << std::endl;
			}
			for (int i = 0; i < player1Hand->size(); i++) {
				if (player1Hand->getButton(i).isSelected) {
					selectedCardButton = &player1Hand->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player1Hand;
					if (player1Hand->getCard(i).getCategory() == ExploitCard) {
						currentState = SelectingTarget;
						actionQueued = true;
					}
					else {
						actionQueued = true;
						currentState = Idle;
					}
					std::cout << "pressed card number " << i << std::endl;
				}
			}
			for (int i = 0; i < player2Hand->size(); i++) {
				if (player2Hand->getButton(i).isSelected) {
					selectedCardButton = &player2Hand->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player2Hand;
					if (player2Hand->getCard(i).getCategory() == ExploitCard) {
						currentState = SelectingTarget;
						actionQueued = true;
					}
					else {
						actionQueued = true;
						currentState = Idle;
					}
				}
			}
			for (int i = 0; i < player1Active->size(); i++) {
				if (player1Active->getButton(i).isSelected) {
					selectedCardButton = &player1Active->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player1Active;
					currentState = Idle;
				}
			}
			for (int i = 0; i < player2Active->size(); i++) {
				if (player2Active->getButton(i).isSelected) {
					selectedCardButton = &player2Active->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player2Active;
					currentState = Idle;
				}
			}
			mouseClicked = true;
		}
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouseClicked = false;
		}
	default:
		break;
	}
}

void Game::handleLogic() {
	if (!actionQueued)
		return;
	if (selectedCardVector == player1Hand) {
		if (selectedCardVector->getCard(selectedCardIndex).getCategory() == DefenseCard) {
			if (player1Active->size() < 6) {
				player1Active->addCard(selectedCardVector->getCard(selectedCardIndex));
				selectedCardVector->removeCard(selectedCardIndex);
				actionQueued = false;
			}
		}
	}
	else if (selectedCardVector == player2Hand) {
		if (selectedCardVector->getCard(selectedCardIndex).getCategory() == DefenseCard) {
			if (player2Active->size() < 6) {
				player2Active->addCard(selectedCardVector->getCard(selectedCardIndex));
				selectedCardVector->removeCard(selectedCardIndex);
				actionQueued = false;
			}
		}
	}
}

void Game::update() {
	/*
	Not planning on actually updating things directly here, 
	but calling the update() functions of other objects
	*/
	manager.refresh();
	startButton->update(*mouse);
	player1Hand->update(*mouse);
	player2Hand->update(*mouse);
	player1Active->update(*mouse);
	player2Active->update(*mouse);
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
	player1Hand->draw();
	player2Hand->draw();
	player1Active->draw();
	player2Active->draw();
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