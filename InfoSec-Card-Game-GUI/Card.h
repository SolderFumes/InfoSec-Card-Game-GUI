#ifndef CARD_H
#define CARD_H

#include <string>
#include <regex>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
using namespace std;

enum AttackSurface { SocialEngineering, DoS, Web, Network };
const string attackSurfaceNames[]{ "Social Engineering", "DoS", "Web", "Network" };

const string DEFAULT_NAME = "NoName";
const string DEFAULT_DESCRIPTION = "NoDescription";
const int DEFAULT_BANDWIDTH_COST = 1;
const AttackSurface DEFAULT_ATTACK_SURFACE = SocialEngineering;

class Card {

public:
    //CONSTRUCTORS
    Card(); //sets all private members to default values
    Card(string, string, int, string, AttackSurface); //initializes all 3 private members
    
    //GETTERS
    string getCardName() const { return cardName; };
    string getCardDescription() const { return cardDescription; };
    int getBandwidthCost() const { return bandwidthCost; };
    AttackSurface getAttackSurface() const { return attackSurface; };
    //SETTERS
    void setCardName(string);
    void setCardDescription(string);
    void setBandwidthCost(int);
    void setTex(const char* path);
    void setAttackSurface(AttackSurface);


    virtual void display() const;
    virtual string toString() const;


    void draw(SDL_Rect& destRect);

protected:
	string cardName;
    string cardDescription;
    int bandwidthCost;
    SDL_Texture* tex;
    AttackSurface attackSurface;
};

#endif /* CARD_H */