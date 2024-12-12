#include "CardVector.h"

CardVector::CardVector(int size, int ypos) {
	maxSize = size;
	this->ypos = ypos;
}

void CardVector::addCard(Card cardToAdd) {
	if (cards.size() < maxSize) {
		cards.push_back(cardToAdd);
		Button newButton(cardToAdd.getTex());
		buttons.push_back(newButton);
	}
	else {
		std::cout << "Cards vector full. Cannot add card." << std::endl;
	}
}
void CardVector::removeCard(int index) {
	if (index >= 0 && index < cards.size()) {
		cards.erase(cards.begin() + index);
		buttons.erase(buttons.begin() + index);
	}
	else {
		throw std::out_of_range("removeCard index out of bounds!");
	}
}
Card CardVector::getCard(int index) {
	if (index >= 0 && index < cards.size()) {
		return cards.at(index);
	}
	else {
		throw std::out_of_range("getCard index out of bounds!");
	}
}
Card* CardVector::getCardPtr(int index) {
	if (index >= 0 && index < cards.size()) {
		return &cards.at(index);
	}
	else {
		throw std::out_of_range("getCardPtr index out of bounds!");
	}
}

Button& CardVector::getButton(int index) {
	if (index >= 0 && index < cards.size()) {
		return buttons.at(index);
	}
	else {
		throw std::out_of_range("getButton index out of bounds!");
	}
}

void CardVector::update(Mouse& mouse) {
	for (Button& b : buttons) b.update(mouse);
}

//Button& CardVector::getClosestButton(Mouse& mouse) {
//	int closestIndex = 0;
//	int lowestDifference = INT_MAX;
//	//find the difference between the mouse's position and the card's position
//	int totalMousePos = mouse.getCollisionPoint()->x + mouse.getCollisionPoint()->y;
//	for (int i = 0; i < cards.size(); i++) {
//		
//		int totalCardPos = cards.at(i).getX() + cards.at(i).getY();
//		int difference = fabs(totalMousePos - totalCardPos);
//		if (difference < lowestDifference) {
//			lowestDifference = difference;
//			closestIndex = i;
//		}
//	}
//	return buttons.at(closestIndex);
//}

void CardVector::draw() {
	for (int i = 0; i < cards.size(); i++) {
		if (cards.at(i).update()) {
			removeCard(i);
			
		}
	}
	for (int i = 0; i < cards.size(); i++) {
		SDL_Rect destRect;
		destRect.x = xpos + (i * cardWidth);
		destRect.y = ypos;
		destRect.w = cardWidth;
		destRect.h = cardHeight;
		cards.at(i).setX(destRect.x);
		cards.at(i).setY(destRect.y);
		buttons.at(i).setDest(destRect);
		buttons.at(i).draw();
	/*	cards.at(i).draw(destRect);*/
	}
}