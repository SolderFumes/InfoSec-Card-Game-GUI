#include "Card.h"
namespace {
    const int cardWidth = 128;
    const int cardHeight = 192;
    const int cardGap = 25;
}

using namespace std;

//CONSTRUCTORS
Card::Card() {
    cardName = DEFAULT_NAME;
    cardDescription = DEFAULT_DESCRIPTION;
    bandwidthCost = DEFAULT_BANDWIDTH_COST;
    attackSurface = DEFAULT_ATTACK_SURFACE;
    category = DEFAULT_CATEGORY;
}

Card::Card(string newName, string newDescription,
    int newBandwidthCost, AttackSurface newAttackSurface, Category newCategory) {
    cardName = newName;
    cardDescription = newDescription;
    bandwidthCost = newBandwidthCost;
    attackSurface = newAttackSurface;
    category = newCategory;
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

void Card::setHealth(int newHealth) {
    if (category == DefenseCard) {
        health = newHealth;
    }
    else {
        throw new exception("tried to set the health of an ExploitCard");
    }
}

void Card::setDamage(int newDamage) {
    if (category == ExploitCard) {
        damage = newDamage;
    }
    else {
        throw new exception("tried to set the damage of a DefenseCard");
    }
}

void Card::setTex(const char* path) {
    tex = TextureManager::LoadTexture(path);
}

void Card::setAttackSurface(AttackSurface newAttackSurface) { attackSurface = newAttackSurface; }

void Card::draw(SDL_Rect& destRect) {
    TextureManager::Draw(tex, destRect);
}

void Card::Attack(Card& target) {
    if (!target.category == DefenseCard) {
        throw new exception("tried to attack an exploitcard");
    }
    else {
        target.reduceCardHealth(damage);
    }
}
void Card::Attack(Entity& target) {
    target.getComponent<PlayerInfoComponent>().incrementHealth(-damage);
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