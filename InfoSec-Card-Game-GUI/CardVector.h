#ifndef CARD_VECTOR_H
#define CARD_VECTOR_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "Button.h"

//This class is a wrapper for a vector of cards with some special methods.

class CardVector {

public:
	CardVector(int size, int ypos);
	void addCard(Card cardToAdd);
	void removeCard(int index);
	std::vector<Card>& getCardsVector() { return cards; };
	Card getCard(int index);
	Card* getCardPtr(int index);
	Button& getButton(int index);
	bool hasDefense();
	int size() { return cards.size(); };

	void setX(int x) { xpos = x; }

	//Button& getClosestButton(Mouse& mouse);

	void update(Mouse&);
	void draw();

private:
	std::vector<Card> cards;
	std::vector<Button> buttons;
	size_t maxSize;
	int xpos, ypos;
	const int cardWidth = 120;
	const int cardHeight = 180;
	const int cardGap = 50;
};

#endif /* CARD_VECTOR_H */