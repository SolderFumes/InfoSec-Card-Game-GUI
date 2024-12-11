#ifndef CARD_VECTOR_H
#define CARD_VECTOR_H

#include <vector>
#include <iostream>
#include "Card.h"

//This class is a wrapper for a vector of cards with some special methods.

class CardVector {

public:
	CardVector(int size, int ypos);
	void addCard(Card& cardToAdd);
	void removeCard(int index);
	std::vector<Card>& getCardsVector() { return cards; };
	Card getCard(int index);

	void update();
	void draw();

private:
	std::vector<Card> cards;
	size_t maxSize;
	int ypos;
	const int cardWidth = 160;
	const int cardHeight = 240;
	const int cardGap = 50;
};

#endif /* CARD_VECTOR_H */