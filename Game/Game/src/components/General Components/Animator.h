#pragma once
#include "Image.h"
#include <unordered_map>
#include <unordered_set>
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
	float srcRectRelativeWidth = 1;
	float srcRectRelativeHeight = 1;

	std::unordered_map<std::string, std::unordered_set<std::string>> linkedAnimations;
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
	// Inicia una nueva animación si es diferente a la actual
	bool playDiff(string key);


	// Actualiza el frame actual dependiendo del frameRate
	virtual void update();
	// Renderiza el frame actual
	virtual void render() const;

	// Asigna el valor para el cambio del tamaño del srcRect
	void setSrcRectRelativeWidth(float rw);
	// Asigna el valor para el cambio del tamaño del srcRect
	void setSrcRectRelativeHeight(float rh);


	// Devuelve el nombre de la animacion actual
	inline string currentAnimationKey() { return currentAnimKey; }

	// Devuelve si la animación actual está corriendo
	inline bool isPlaying() {
		return currentAnimation != nullptr && repetitions != currentAnimation->repeat;
	}
	// Devuelve si la animación actual se ha completado
	inline bool animationComplete() {
		return currentAnimation != nullptr && repetitions == currentAnimation->repeat;
	}
	// Devuelve si la animación actual es la introducida
	inline bool isCurrentAnimation(string key) {
		return currentAnimKey == key;
	}
	//Devuelve si la animacion introducida esta siendo reproducida
	inline bool isPlaying(string key) {
		return isCurrentAnimation(key) && isPlaying();
	}

	// Enlaza dos animaciones, es decir, al cambiar entre estas dos el frame actual no cambiará
	void linkAnimations(std::string key1, std::string key2);
};