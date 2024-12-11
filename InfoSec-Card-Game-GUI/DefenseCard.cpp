#include "DefenseCard.h"
namespace {
    const int cardWidth = 160;
    const int cardHeight = 240;
    const int cardGap = 50;
    int DEFAULT_CARD_HEALTH = 50;
}

using namespace std;

//constructors :
DefenseCard::DefenseCard() : Card() {
    cardHealth = DEFAULT_CARD_HEALTH;
}

DefenseCard::DefenseCard(string newName, string newDescription, int newBandwidthCost,
    string newImageLink, AttackSurface newAttackSurface, int newHealth) :
    Card(newName, newDescription, newBandwidthCost, newImageLink, newAttackSurface) {
    cardHealth = newHealth;
}

//GETTER
int DefenseCard::getCardHealth() const { return cardHealth; }

//SETTER
void DefenseCard::setCardHealth(int newHealth) { cardHealth = newHealth; }

int DefenseCard::reduceCardHealth(int reduceBy) {
    int difference = cardHealth - reduceBy; //<-- returns a negative value if there
    //is leftover damage.
    cardHealth -= reduceBy;
    return difference;
}

//OTHER METHODS
void DefenseCard::display() const {
    Card::display();
    cout << " This card has " << cardHealth << " health.";
}

string DefenseCard::toString() const {
    string resultString = Card::toString();
    resultString += " | Health: " + to_string(cardHealth);

    return resultString;
}