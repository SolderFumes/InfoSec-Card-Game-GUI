#include "Button.h"

//Button::Button() {
//	//this is a sprite sheet!
//	static SDL_Texture* spriteSheet = TextureManager::LoadTexture("spriteSheet.png");
//	tex = spriteSheet;
//
//	//this is the size of each tile in my PyxelEdit spriteSheet
//	srcRect.h = 64;
//	srcRect.w = 128;
//	//I will always be starting on the left of a texture, but I might be moving the Y if I am selecting 
//	//different sprite on the spriteSheet yk
//	srcRect.x = 0;
//	srcRect.y = 0;
//
//	//This will scale how big the button appears when drawn, I'm keeping it the same
//	//but I could theoretically change this later.
//	destRect.h = 64;
//	destRect.w = 128;
//	
//}

Button::Button() {
	tex = TextureManager::LoadTexture("blank.png");
}

	
void Button::setDest(SDL_Rect newDestRect) {
	destRect = newDestRect;
}

void Button::update(Mouse& mouse) {

	//check if our button is intersecting with the collision point of our mouse
	if (SDL_HasIntersection(&destRect, mouse.getCollisionPoint())) {
		isSelected = true;
		//since the selected part of my spriteSheet is on the Y axis, we will shift to the selected
		//version of our button.
		//!TODO change the sprite sheet to have selected button on x axis so that Y axis can be used to iterate
		//! through different buttons :)
		srcRect.y = 64;
	}
	else {
		isSelected = false;
		srcRect.y = 0;
	}
}

void Button::draw() {
	TextureManager::Draw(tex, destRect);
}