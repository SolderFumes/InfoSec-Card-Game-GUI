#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H
#include "Components.h"
#include "SDL_ttf.h"

class TextComponent : public Component {
public:
	TextComponent() {
		text = "blank text";
	}
	
	TextComponent(const char* newText) {
		text = newText;
	}
	

	void init() override {
		position = &entity->getComponent<PositionComponent>();

		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color White = { 255, 255, 255, 255 };

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		TTF_Font* font = TTF_OpenFont("binchrt.ttf", 24);
		if (font == NULL) {
			std::cout << "Error opening font in TextComponent" << std::endl;
		}
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
		if (surfaceMessage == NULL) {
			std::cout << "Error creating surfaceMessage in TextComponent." << std::endl;
			std::cout << TTF_GetError() << std::endl;
		}
		// now you can convert it into a texture
		Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

		Message_rect.w = Game::widthSegment; // controls the width of the rect
		Message_rect.h = Game::heightSegment; // controls the height of the rect
		Message_rect.x = position->x() + 2*Game::widthSegment;  //controls the rect's x coordinate 
		Message_rect.y = position->y(); // controls the rect's y coordinte

	}

	void setName(const char* newText) {
		text = newText;
		//draw a different texture based on the health

		// this is the color in rgb format,
		// maxing out all would give you the color white,
		// and it will be your text's color
		SDL_Color White = { 255, 255, 255, 255 };

		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		TTF_Font* font = TTF_OpenFont("binchrt.ttf", 24);
		if (font == NULL) {
			std::cout << "Error opening font in TextComponent" << std::endl;
		}
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
		if (surfaceMessage == NULL) {
			std::cout << "Error creating surfaceMessage in TextComponent." << std::endl;
			std::cout << TTF_GetError() << std::endl;
		}
		// now you can convert it into a texture
		Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

		Message_rect.w = Game::widthSegment; // controls the width of the rect
		Message_rect.h = Game::heightSegment; // controls the height of the rect
		Message_rect.x = position->x() + 2*Game::widthSegment;  //controls the rect's x coordinate 
		Message_rect.y = position->y(); // controls the rect's y coordinte
		
		TTF_CloseFont(font);
	}

	void update() override {
		
	}
	void draw() override {
		TextureManager::Draw(Message, Message_rect);
	}
	
	PositionComponent* position;
	const char* text;
	SDL_Texture* Message;
	SDL_Rect Message_rect;
};

#endif /* TEXT_COMPONENT_H */