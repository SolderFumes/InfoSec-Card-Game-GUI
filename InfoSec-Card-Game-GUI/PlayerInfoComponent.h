#ifndef PLAYER_INFO_COMPONENT_H
#define PLAYER_INFO_COMPONENT_H

#include "Components.h"
#include "SDL_ttf.h"
#include "Game.h"

class PlayerInfoComponent : public Component {
public:
	PlayerInfoComponent() {
		name = "Unnamed Player";
		health = 100;
		bandwidth = 100;
	}
	
	PlayerInfoComponent(int health, int bandwidth, const char* name) {
		this->health = health;
		this->bandwidth = bandwidth;
		this->name = name;
	}

	int getHealth() const { return health; };
	int getBandwidth() const { return bandwidth; };
	const char* getName() const { return name; };

	void incrementHealth(int incrementBy) {
		health += incrementBy;
	}
	void incrementBandwidth(int incrementBy) {
		bandwidth += incrementBy;
	}

	void init() override {
		sprite = &entity->getComponent<SpriteComponent>();
		position = &entity->getComponent<PositionComponent>();
		//draw a different texture based on the health

		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color Black = { 0, 0, 0, 255 };

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		TTF_Font* font = TTF_OpenFont("binchrt.ttf", 64);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, name, Black);
		if (surfaceMessage == NULL) {
			std::cout << "Error creating surfaceMessage." << std::endl;
			std::cout << TTF_GetError() << std::endl;
		}
		// now you can convert it into a texture
		Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

		Message_rect.w = Game::widthSegment * 2; // controls the width of the rect
		Message_rect.h = Game::heightSegment; // controls the height of the rect
		int centeredxpos = Game::widthSegment * 5;
		centeredxpos -= Message_rect.w / 2;
		Message_rect.x = centeredxpos;  //controls the rect's x coordinate 
		Message_rect.y = (int)(position->y() * 1.1); // controls the rect's y coordinte

		TTF_CloseFont(font);
	};
	void update() override {
		
	};
	void draw() override {
		
		TextureManager::Draw(Message, Message_rect);
	}
private:
	PositionComponent* position;
	SpriteComponent* sprite;
	int health;
	int bandwidth;
	const char* name;
	SDL_Texture* Message;
	SDL_Rect Message_rect;
};

#endif /* PLAYER_INFO_COMPONENT_H */