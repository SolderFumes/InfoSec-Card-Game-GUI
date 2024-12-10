#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect) {
	SDL_RenderCopy(Game::renderer, tex, &srcRect, &destRect);
}

//this allows us to not specify a srcRect  but still use TextureManager
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect destRect) {
	SDL_RenderCopy(Game::renderer, tex, NULL, &destRect);
}