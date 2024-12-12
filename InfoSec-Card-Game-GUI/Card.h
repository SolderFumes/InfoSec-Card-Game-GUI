#ifndef CARD_H
#define CARD_H

#include <string>
#include <regex>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "ECS.h"
#include "Components.h"
using namespace std;

enum AttackSurface { SocialEngineering, DoS, Web, Network };
enum Category { DefenseCard, ExploitCard };
const string attackSurfaceNames[]{ "Social Engineering", "DoS", "Web", "Network" };

const string DEFAULT_NAME = "NoName";
const string DEFAULT_DESCRIPTION = "NoDescription";
const int DEFAULT_BANDWIDTH_COST = 1;
const AttackSurface DEFAULT_ATTACK_SURFACE = SocialEngineering;
const Category DEFAULT_CATEGORY = DefenseCard;

class Card {

public:
    //CONSTRUCTORS
    Card(); //sets all private members to default values
    Card(string, string, int, AttackSurface, Category);
    
    //GETTERS
    string getCardName() const { return cardName; };
    string getCardDescription() const { return cardDescription; };
    int getBandwidthCost() const { return bandwidthCost; };
    AttackSurface getAttackSurface() const { return attackSurface; };
    Category getCategory() const { return category; }
    int getX() { return xpos; };
    int getY() { return ypos; };
    //SETTERS
    void setCardName(string);
    void setCardDescription(string);
    void setBandwidthCost(int);
    void setHealth(int);
    void setDamage(int);
    void setTex(const char* path);
    void setAttackSurface(AttackSurface);
    void setX(int newX) { xpos = newX; };
    void setY(int newY) { ypos = newY; };
    int reduceCardHealth(int reduceBy) {
        int difference = health - reduceBy; //<-- returns a negative value if there
        //is leftover damage.
        health -= reduceBy;
        return difference;
    }
    void Attack(Card& target);
    void Attack(Entity& targetPlayer);


    void display() const;
    string toString() const;


    void draw(SDL_Rect& destRect);

private:
	string cardName;
    string cardDescription;
    int bandwidthCost;
    AttackSurface attackSurface;
    int health;
    int damage;
    Category category;

    SDL_Texture* tex;
    int xpos, ypos;
};

#endif /* CARD_H */