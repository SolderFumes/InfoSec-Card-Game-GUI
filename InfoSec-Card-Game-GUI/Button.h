#ifndef BUTTON_H
#define BUTTON_H
#include "SDL.h"
#include "TextureManager.h"
#include "Mouse.h"

class Button {
public:
	Button();

	void update(Mouse& mouse);
	void draw();

	SDL_Texture* tex;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	bool isSelected = false;
};

#endif /* BUTTON_H */