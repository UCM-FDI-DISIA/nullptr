#pragma once
#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Image.h"
#include <unordered_map>

/*struct Animation {
	int startFrame, endFrame;
	int frameRate;
	int repeat;
	Animation() {}
	Animation(int _s, int _e, int _rate, int _rep) : startFrame(_s), endFrame(_e), frameRate(_rate), repeat(_rep) {}
};*/

using AnimationMap = unordered_map<string, Animation>;

class Animator : public Image {
private:
	// Variables de tamaño, filas y columnas de la spritesheet
	int fw, fh, rows, cols;
	int currentFrame;
	int repetitions;
	double currTime;
	AnimationMap anims;
	string currentAnimKey;
	Animation* currentAnimation;
public:
	// Constructora
	Animator(Texture* _texture, int _w, int _h, int _r, int _c) :
		Image(_texture), fw(_w), fh(_h), rows(_r), cols(_c), currentFrame(0), currTime(0), repetitions(0), currentAnimation(nullptr) { };

	// Crea una animacion nueva
	void createAnim(string key, Animation anim);
	// Crea una animacion nueva
	void createAnim(string key, int start, int end, int rate, int _rep = 0);

	// Empieza una nueva animacion
	void play(string key);

	// Para la animacion actual
	void stop();

	// Continua la ultima animacion
	void resume();
	
	// Actualiza el frame actual dependiendo del frameRate
	virtual void update();

	// Renderiza el frame actual
	virtual void render() const;

	// Devuelve el nombre de la animacion actual
	inline string currentAnimationKey() { return currentAnimKey; }

	// Devuelve el numero del frame actual
	inline int getCurrentFrame() { return currentFrame; }
};
#endif // !ANIMATOR_H_