#ifndef PLAYER_H
#define PLAYER_H
#include "Game.h"
#include "ECS.h"
#include "TextureManager.h"

class Player : public Entity {
public:

	void init();

	int getHP() const { return hp; };
	const char* getPlayerName() const { return playerName; };

private:
	const char* playerName;
	int hp;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* tex;
};

#endif /* PLAYER_H */