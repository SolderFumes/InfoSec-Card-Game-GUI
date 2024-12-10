#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
public:
	//specify default constructor since we implemented non-default ones
	SpriteComponent() = default;
	SpriteComponent(int w, int h, const char* texturePath) {
		width = w;
		height = h;
		setTex(texturePath);
	}
	SpriteComponent(const char* texturePath) {
		setTex(texturePath);
	}

	void setTex(const char* texturePath) {
		texture = TextureManager::LoadTexture(texturePath);
	}
	void setWidth(int w) {
		width = w;
	}
	void setHeight(int h) {
		height = h;
	}
	int getWidth() { return width; }
	int getHeight() { return height;  }

	void init() override {
		
		position = &entity->getComponent<PositionComponent>();
		
		srcRect.x = srcRect.y = 0;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
	}
	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int height;
	int width;
};

#endif /* SPRITE_COMPONENT_H */