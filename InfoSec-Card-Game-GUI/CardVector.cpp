#include "CardVector.h"

CardVector::CardVector(int size, int ypos) {
	maxSize = size;
	this->ypos = ypos;
}

void CardVector::addCard(Card& cardToAdd) {
	if (cards.size() < maxSize) {
		cards.push_back(cardToAdd);
	}
	else {
		std::cout << "Cards vector full. Cannot add card." << std::endl;
	}
}
void CardVector::removeCard(int index) {
	if (index > 0 && index < cards.size()) {
		cards.erase(cards.begin() + index);
	}
	else {
		throw std::out_of_range("removeCard index out of bounds!");
	}
}
Card CardVector::getCard(int index) {
	if (index > 0 && index < cards.size()) {
		return cards.at(index);
	}
	else {
		throw std::out_of_range("getCard index out of bounds!");
	}
}

void CardVector::draw() {
	for (int i = 0; i < cards.size(); i++) {
		SDL_Rect destRect;
		destRect.x = Game::widthSegment/2 + (i * cardWidth);
		destRect.y = ypos;
		destRect.w = cardWidth;
		destRect.h = cardHeight;
		cards.at(i).draw(destRect);
	}
}