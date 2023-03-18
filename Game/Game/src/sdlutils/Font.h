// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_ttf.h>
#include <string>
#include <cassert>
#include <iostream>

#include "macros.h"

class Font {
public:

	// cannot copy objects of this type!
	Font(const Font &other) = delete;
	Font& operator=(const Font &other) = delete;

	// can be moved
	Font& operator=(Font &&other) noexcept {
		this->~Font();
		font_ = other.font_;
		other.font_ = nullptr;
		return *this;
	}

	Font(Font &&other) noexcept {
		font_ = other.font_;
		other.font_ = nullptr;
	}

	Font(const std::string &fileName, int size) {
		font_ = TTF_OpenFont(fileName.c_str(), size);
		if (font_ == nullptr) {
			throw "Couldn't load font: " + fileName;
		}
	}

	virtual ~Font() {
		if (font_ != nullptr)
			TTF_CloseFont(font_);
	}

	inline SDL_Surface* renderText(const std::string &text,
			SDL_Color fgColor) const {
		assert(font_ != nullptr);
		return TTF_RenderUTF8_Solid(font_, text.c_str(), fgColor);
	}

	inline SDL_Surface* renderText(const std::string &text, SDL_Color fgColor,
			SDL_Color bgColor) const {
		assert(font_ != nullptr);
		return TTF_RenderUTF8_Shaded(font_, text.c_str(), fgColor, bgColor);
	}

	inline SDL_Surface* renderText(const std::string &text,
			SDL_Color fgColor, float width) const {
		assert(font_ != nullptr);
		return TTF_RenderText_Solid_Wrapped(font_, text.c_str(), fgColor, width);
	}

	inline SDL_Surface* renderText(const std::string &text, SDL_Color fgColor,
			SDL_Color bgColor, float width) const {
		assert(font_ != nullptr);
		return TTF_RenderText_Shaded_Wrapped(font_, text.c_str(), fgColor, bgColor, width);
	}

private:
	TTF_Font *font_;
}
;
