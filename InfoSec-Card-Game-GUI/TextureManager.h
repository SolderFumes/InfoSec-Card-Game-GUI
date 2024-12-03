#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect);
};

#endif /* TEXTURE_MANAGER_H */