#ifndef DEFENSE_CARD_H
#define DEFENSE_CARD_H

#include "Card.h"
class DefenseCard : public Card {
public:
    //CONSTRUCTORS
    DefenseCard();
    DefenseCard(string, string, int, string, AttackSurface, int);

    //GETTER
    int getCardHealth() const;

    //SETTER
    void setCardHealth(int);
    int reduceCardHealth(int reduceBy); //return the difference between cardHealth
    // and reduceby, therefore finding if theres any leftover damage :)

    //OTHER METHODS
    void display() const;
    string toString() const;

private:
    int cardHealth;
};

#endif /* DEFENSE_CARD_H */