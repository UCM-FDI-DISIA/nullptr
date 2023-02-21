#pragma once
#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Image.h"
#include <unordered_map>

struct Animation {
	int startFrame, endFrame;
	int frameRate;
	int repeat;
	Animation() {}
	Animation(int _s, int _e, int _rate, int _rep) : startFrame(_s), endFrame(_e), frameRate(_rate), repeat(_rep) {}
};

using AnimationMap = unordered_map<string, Animation>;

class Animator : public Image {
private:
	// Variables de tamaño, filas y columnas de la spritesheet
	int fw, fh, rows, cols;
	int currentFrame;
	int repetitions;
	uint startTime;
	AnimationMap anims;
	string currentAnimKey;
	Animation* currentAnimation;
public:
	static const int id = _ANIMATOR;
	Animator(Texture* _texture, int _w, int _h, int _r, int _c) :
		Image(_texture), fw(_w), fh(_h), rows(_r), cols(_c), currentFrame(0), repetitions(0), startTime(SDL_GetTicks()), currentAnimation(nullptr) { };

	//Animaciones
	void createAnim(string key,int start, int end, int rate, int _rep = 0);
	void play(string key);
	void stop();
	void resume();
	
	//Metodos esenciales
	virtual void update();
	virtual void render() const;

	//Getters
	inline string currentAnimationKey() { return currentAnimKey; }
	inline int getCurrentFrame() { return currentFrame; }
};

#endif // !ANIMATOR_H_