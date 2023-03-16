#pragma once

#include "Image.h"
#include "../../sdlutils/SDLUtils.h"

class TextComponent : public Image {
private:
	Font* font;
	std::string text;
	SDL_Color color;
	Texture texture;
public:
	TextComponent(Font* _f, std::string _text, SDL_Color _color = build_sdlcolor("0x000000")) :
		Image(&texture),
		font(_f), text(_text), color(_color),
		texture(sdlutils().renderer(), text, *font, color) {}
	virtual void initComponent() {
		Image::initComponent();
		transform->setHeight(texture.height() * 5);
		transform->setWidth(texture.width() * 5);
	}
	void reloadTexture() { 
		transform->setHeight(transform->getHeight() / texture.height());
		transform->setWidth(transform->getWidth() / texture.width());
		texture = Texture(sdlutils().renderer(), text, *font, color);
		transform->setHeight(transform->getHeight() * texture.height());
		transform->setWidth(transform->getWidth() * texture.width());
	}
	void changeText(std::string newText) { text = newText; reloadTexture(); }
	void changeFont(Font* newFont) { font = newFont; reloadTexture(); }
	void changeColor(SDL_Color newColor) { color = newColor; reloadTexture(); }
	void changeColor(std::string newColorHex) { changeColor(build_sdlcolor(newColorHex)); }

	TextComponent& operator +=(std::string s) {
		changeText(text + s);
		return *this;
	}
};

