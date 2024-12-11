#include "Card.h"
namespace {
    const int cardWidth = 160;
    const int cardHeight = 240;
    const int cardGap = 50;
}

using namespace std;

//CONSTRUCTORS
Card::Card() {
    cardName = DEFAULT_NAME;
    cardDescription = DEFAULT_DESCRIPTION;
    bandwidthCost = DEFAULT_BANDWIDTH_COST;
    attackSurface = DEFAULT_ATTACK_SURFACE;
}

Card::Card(string newName, string newDescription,
    int newBandwidthCost, string newImageLink, AttackSurface newAttackSurface) {
    cardName = newName;
    cardDescription = newDescription;
    bandwidthCost = newBandwidthCost;
    attackSurface = newAttackSurface;
}

//SETTERS

void Card::setCardName(string newName) { cardName = newName; }

void Card::setCardDescription(string newDescription) { cardDescription = newDescription; }

void Card::setBandwidthCost(int newBandwidthCost) {
    //data validation!
    if (newBandwidthCost >= 0) {
        bandwidthCost = newBandwidthCost;
    }
    else {
        cout << "Invalid Bandwidth Cost!" << endl;
    }
}

void Card::setTex(const char* path) {
    tex = TextureManager::LoadTexture(path);
}

void Card::setAttackSurface(AttackSurface newAttackSurface) { attackSurface = newAttackSurface; }

void Card::draw(SDL_Rect& destRect) {
    TextureManager::Draw(tex, destRect);
}

//OTHER METHODS
void Card::display() const {
    cout << getCardName() << ": " << getCardDescription() << ". Costs " << getBandwidthCost()
        << " bandwidth. Attack surface is " << attackSurfaceNames[getAttackSurface()] << ".";
}

string Card::toString() const {
    string returnString = "Name: " + getCardName();
    returnString += " | Description: " + getCardDescription();
    returnString += " | Bandwidth Cost: " + to_string(getBandwidthCost());
    returnString += " | Attack Surface: " + attackSurfaceNames[getAttackSurface()];

    return returnString;
}