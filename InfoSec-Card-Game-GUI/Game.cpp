#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Button.h"
#include "CardVector.h"
#include <cmath>
#include <iostream>

Map* map;
Mouse* mouse;
Button* startButton;
Button* endTurnButton;
CardVector* player1Hand;
CardVector* player2Hand;
CardVector* player1Active;
CardVector* player2Active;
Card card2, card3, card4;
Card card1("evil guy", "meanie", 50, Web, ExploitCard);
Manager manager;
Entity& player1(manager.addEntity());
Entity& player2(manager.addEntity());
Entity& turnCounter(manager.addEntity());
Entity& deck(manager.addEntity());
const int drawPileSize = 4;
Card drawPile[drawPileSize];

Button* selectedCardButton;
int selectedCardIndex;
CardVector* selectedCardVector;
bool mouseClicked = false;
bool actionQueued = false;
Card* clickedCards[2] = { nullptr, nullptr };
int clickedCardsTeam[2] = { 0, 0 };
int clickedCardsIndex[2] = { -1, -1 };
int turn = 1;

SDL_Renderer* Game::renderer = nullptr;
//set these static variables to default values
int Game::widthSegment = 0;
int Game::heightSegment = 0;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	srand(time(NULL));

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
	endTurnButton = new Button(TextureManager::LoadTexture("endTurn.png"));
	SDL_Rect* endTurnDest = new SDL_Rect;
	endTurnDest->x = widthSegment * 9;
	endTurnDest->y = heightSegment * 5 - 240;
	endTurnDest->w = 160;
	endTurnDest->h = 240;
	endTurnButton->setDest(*endTurnDest);
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

	turnCounter.addComponent<PositionComponent>(widthSegment * 8, heightSegment * .5);
	turnCounter.addComponent<TextComponent>("Turn 1");

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

	card1.setTex("attackCard.png");
	card2.setTex("card.png");
	card3.setTex("wifi.png");
	card4.setTex("testHand.png");
	card2.setCardName("circle card thingy");
	card3.setCardName("wifi");
	card4.setCardName("kibby :3");
	card1.setDamage(50);
	card2.setHealth(50);
	card3.setHealth(75);
	card4.setHealth(90);
	drawPile[0] = card1;
	drawPile[1] = card2;
	drawPile[2] = card3;
	drawPile[3] = card4;

	//fill each hand with random cards!
	for (int i = 0; i < 4; i++) player1Hand->addCard(drawPile[rand() % drawPileSize]);
	for (int i = 0; i < 4; i++) player2Hand->addCard(drawPile[rand() % drawPileSize]);
	/*player1Active->addCard(card1);
	player1Active->addCard(card2);
	player1Active->addCard(card3);
	player1Active->addCard(card4);
	player2Active->addCard(card1);
	player2Active->addCard(card2);
	player2Active->addCard(card3);
	player2Active->addCard(card4);*/

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
			if (endTurnButton->isSelected) {
				std::cout << "ending turn! :D" << std::endl;
				endTurn();
				return;
			}
			for (int i = 0; i < player1Hand->size(); i++) {
				if (player1Hand->getButton(i).isSelected) {
					selectedCardButton = &player1Hand->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player1Hand;
					if (player1Hand->getCard(i).getCategory() == ExploitCard) {
						actionQueued = true;
					}
					else {
						actionQueued = true;
					}
					return;
				}
			}
			for (int i = 0; i < player2Hand->size(); i++) {
				if (player2Hand->getButton(i).isSelected) {
					selectedCardButton = &player2Hand->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player2Hand;
					if (player2Hand->getCard(i).getCategory() == ExploitCard) {
						actionQueued = true;
					}
					else {
						actionQueued = true;
					}
					return;
				}
			}
			for (int i = 0; i < player1Active->size(); i++) {
				if (player1Active->getButton(i).isSelected) {
					selectedCardButton = &player1Active->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player1Active;
					return;
				}
			}
			for (int i = 0; i < player2Active->size(); i++) {
				if (player2Active->getButton(i).isSelected) {
					selectedCardButton = &player2Active->getButton(i);
					selectedCardIndex = i;
					selectedCardVector = player2Active;
					return;
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
	//check if we clicked on something in player 1's hand
	//also check if it's player 1's turn (odd number)
	if (selectedCardVector == player1Hand && turn % 2 != 0) {
		//if we clicked on a defense card, play it
		if (selectedCardVector->getCard(selectedCardIndex).getCategory() == DefenseCard) {
			if (player1Active->size() < 6) {
				player1Active->addCard(selectedCardVector->getCard(selectedCardIndex));
				selectedCardVector->removeCard(selectedCardIndex);
				actionQueued = false;
				endTurn();
			}
		}
		//if we clicked on an attack card when one HASNT been clicked already, add it to clickedCards
		//also track which team the card we clicked is
		else if (clickedCards[0] == nullptr) {
			clickedCards[0] = selectedCardVector->getCardPtr(selectedCardIndex);
			clickedCardsIndex[0] = selectedCardIndex;
			clickedCardsTeam[0] = 1;
		}
	}
	//now, if we clicked an active card in player2's section, and we have already selected an attack card, 
	// try to attack it!
	// also verifying if we are attacking the right team's cards
	else if (selectedCardVector == player2Active) {
		if (clickedCards[0] != nullptr && clickedCardsTeam[0] == 1) {
			clickedCards[0]->Attack(*(selectedCardVector->getCardPtr(selectedCardIndex)));
			player1Hand->removeCard(clickedCardsIndex[0]);
			clickedCards[0] = nullptr;
			clickedCards[1] = nullptr;
			clickedCardsTeam[0] = 0;
			clickedCardsTeam[1] = 0;
			endTurn();
		}
	}
	else if (selectedCardVector == player2Hand && turn % 2 == 0) {
		if (selectedCardVector->getCard(selectedCardIndex).getCategory() == DefenseCard) {
			if (player2Active->size() < 6) {
				player2Active->addCard(selectedCardVector->getCard(selectedCardIndex));
				selectedCardVector->removeCard(selectedCardIndex);
				actionQueued = false;
				endTurn();
			}
		}
		else if (clickedCards[0] == nullptr) {
				clickedCards[0] = selectedCardVector->getCardPtr(selectedCardIndex);
				clickedCardsIndex[0] = selectedCardIndex;
				clickedCardsTeam[0] = 2;
		}
	}
	else if (selectedCardVector == player1Active) {
		if (clickedCards[0] != nullptr && clickedCardsTeam[0] == 2) {
			clickedCards[0]->Attack(*(selectedCardVector->getCardPtr(selectedCardIndex)));
			player2Hand->removeCard(clickedCardsIndex[0]);
			clickedCards[0] = nullptr;
			clickedCards[1] = nullptr;
			clickedCardsTeam[0] = 0;
			clickedCardsTeam[1]	= 0;
			endTurn();
			
		}
	}
}

void Game::endTurn() {
	//draw!
	//if its p2's turn that just finished..
	if (turn % 2 == 0) {
		//deal both players! this is more card-game-esque imo
		if (player1Hand->size() < 4) {
			player1Hand->addCard(drawPile[rand() % drawPileSize]);
			std::cout << "Dealt player 2 a card!" << std::endl;
		}
		if (player2Hand->size() < 4) {
			player2Hand->addCard(drawPile[rand() % drawPileSize]);
			std::cout << "Dealt player 2 a card!" << std::endl;
		}
	}
	
	//everything from current turn is done!
	turn++;
	string tempstr = "Turn " + to_string(turn);
	turnCounter.getComponent<TextComponent>().setName(tempstr.c_str());
}

void Game::update() {
	/*
	Not planning on actually updating things directly here, 
	but calling the update() functions of other objects
	*/
	manager.refresh();
	startButton->update(*mouse);
	endTurnButton->update(*mouse);
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
	endTurnButton->draw();
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