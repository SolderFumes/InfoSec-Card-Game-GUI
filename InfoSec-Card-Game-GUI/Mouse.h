#ifndef MOUSE_H
#define MOUSE_H

#include "SDL.h"
#include "TextureManager.h"

class Mouse {
public:
	Mouse() {
		tex = TextureManager::LoadTexture("cursor.png");
		rect.w = rect.h = 32;
		//this point is only for collision detection, so it only needs to be one pixel.
		collisionPoint.w = collisionPoint.h = 1;

		SDL_ShowCursor(false);
	}

	SDL_Rect* getCollisionPoint() { return &collisionPoint; }

	void update() {
		SDL_GetMouseState(&rect.x, &rect.y);
		//this will set the collision point of the mouse to be the very top left of the cursor as usual
		collisionPoint.x = rect.x;
		collisionPoint.y = rect.y;
	}

	void draw() {
		//NULL uses the whole image
		//!TODO implement this with TextureManager
		SDL_RenderCopy(Game::renderer, tex, NULL, &rect);
	}
	
	
	
private:
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect collisionPoint;

};

#endif /* MOUSE_H */