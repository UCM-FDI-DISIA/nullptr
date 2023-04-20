// This file is part of the course TPV2@UCM - Samir Genaim

#include "SDLUtils.h"
#include <cassert>
#include <memory>

#include "../data/json/JSON.h"

SDLUtils::SDLUtils() :
		SDLUtils("SDL Demo", 600, 400) {
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height) :
		windowTitle_(windowTitle), //
		width_(width), //
		height_(height), //
		fontsAccessWrapper_(fonts_, "Fonts Table"), //
		imagesAccessWrapper_(images_, "Images Table"), //
		relicsAccessWrapper_(relics_, "Relics Table"),
		//numberCtsAccessWrapper_(numberCts_, "Numbers Table"), //
		soundsAccessWrapper_(sounds_, "Sounds Table"), //
		musicsAccessWrapper_(musics_, "Musics Table") ///
{

	initWindow();
	initSDLExtensions();
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height,
		std::string filename) :
		SDLUtils(windowTitle, width, height) {
	loadResources(filename);
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
	closeWindow();
}

void SDLUtils::initWindow() {

#ifdef _DEBUG
	std::cout << "Initializing SDL" << std::endl;
#endif

	// initialise SDL
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

#ifdef _DEBUG
	std::cout << "Creating SDL window" << std::endl;
#endif

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

#ifdef _DEBUG
	std::cout << "Creating SDL renderer" << std::endl;
#endif
	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	// hide cursor by default
	//hideCursor();
	SDL_RenderSetIntegerScale(renderer_, SDL_bool(true));
}

void SDLUtils::closeWindow() {

	// destroy renderer and window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	SDL_Quit(); // quit SDL
}

void SDLUtils::initSDLExtensions() {

#ifdef _DEBUG
	std::cout << "Initializing SDL_ttf" << std::endl;
#endif
	// initialize SDL_ttf
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);

#ifdef _DEBUG
	std::cout << "Initializing SDL_img" << std::endl;
#endif
	// initialize SDL_image
	int imgInit_ret = IMG_Init(
			IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);

#ifdef _DEBUG
	std::cout << "Initializing SEL_Mixer" << std::endl;
#endif
	// initialize SDL_Mixer
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);
	int mixInit_ret = Mix_Init(
			MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);
	SoundEffect::setNumberofChannels(8); // we start with 8 channels

}

void SDLUtils::loadResources(std::string filename) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue *jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	// load fonts
	jValue = root["fonts"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			fonts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					uint8_t size =
							static_cast<uint8_t>(vObj["size"]->AsNumber());
#ifdef _DEBUG
					std::cout << "Loading font with id: " << key << std::endl;
#endif
					fonts_.emplace(key, Font(file, size));
				} else {
					throw "'fonts' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}

	// load images
	jValue = root["images"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			images_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading image with id: " << key << std::endl;
#endif
					images_.emplace(key, Texture(renderer(), file));
				} else {
					throw "'images' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'images' is not an array in '" + filename + "'";
		}
	}

	// load relics
	jValue = root["relics"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			relics_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string description = vObj["description"]->AsString();
					std::string era = vObj["era"]->AsString();
					std::string health = vObj["health"]->AsString();
					std::string movementVelocity = vObj["movementVelocity"]->AsString();
					std::string cadency = vObj["cadency"]->AsString();
					std::string mana = vObj["mana"]->AsString();
					std::string attack = vObj["attack"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading relic info with id: " << key << std::endl;
#endif
					Relic relicStruct(&images().at(key), description, era, stoi(health), stoi(movementVelocity), stoi(cadency), stoi(mana), stoi(attack));
					
					relics_.emplace(key, relicStruct);
				}
				else {
					throw "'relics' array in '" + filename
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'relics' is not an array in '" + filename + "'";
		}
	}

//	// load number constants
//	jValue = root["number"];
//	if (jValue != nullptr) {
//		if (jValue->IsArray()) {
//			numberCts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
//			for (auto &v : jValue->AsArray()) {
//				if (v->IsObject()) {
//					JSONObject vObj = v->AsObject();
//					std::string key = vObj["id"]->AsString();
//					double value = vObj["value"]->AsNumber();
//#ifdef _DEBUG
//					std::cout << "Loading number (int, float, double) info with id: " << key << std::endl;
//#endif
//
//					numberCts_.emplace(key, value);
//					
//				} else {
//					throw "'number' array in '" + filename
//							+ "' includes and invalid value";
//				}
//			}
//		} else {
//			throw "'number' is not an array in '" + filename + "'";
//		}
//	}

// load sounds
	jValue = root["sounds"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			sounds_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading sound effect with id: " << key
							<< std::endl;
#endif
					sounds_.emplace(key, SoundEffect(file));
				} else {
					throw "'sounds' array in '" + filename
							+ "' includes and invalid value";
				}
		}
		} else {
			throw "'sounds' is not an array";
		}
	}
//
//	// load musics
	jValue = root["musics"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			musics_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading music with id: " << key << std::endl;
#endif
					musics_.emplace(key, Music(file));
				} else {
					throw "'musics' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'musics' is not an array";
		}
	}

}

void SDLUtils::closeSDLExtensions() {

	musics_.clear();
	sounds_.clear();
	//msgs_.clear();
	images_.clear();
	fonts_.clear();

	Mix_Quit(); // quit SDL_mixer
	IMG_Quit(); // quit SDL_image
	TTF_Quit(); // quit SDL_ttf
}

