#pragma once
#include "Animator.h"
class CharacterAnimator : public Animator {
protected:
	// Indica si se quiere que el sprite haga flip dependiendo de su dirección
	bool wantToAdjustDirection;
	// Guarda keys de animaciones con la condición sobre la que se ejecutará dicha animación
	unordered_map<string, BoolCallBack> actions;
public:
	// Constructora, recibe animaciones de idle y movimiento
	CharacterAnimator(Texture* _texture, int _w, int _h, int _r, int _c, Animation idle, Animation move);
	// Actualiza la animacion del personaje en función a sus acciones
	virtual void update();


	// Actualiza a la animación correspondiente a la acción actual, devuelve si ha cambiado de animación o no
	virtual bool updatePlayingAnimation();


	// Añade una nueva animación que iniciará cuando el callback pasado devuelva true
	void addAction(string key, Animation anim, BoolCallBack cb);
	// Añade animación de ataque que iniciará cuando el callback pasado devuelva true
	void addAttack(Animation anim, BoolCallBack cb);


	// Devuelve si la acción del jugador es idle, siempre se comprueba la última
	virtual bool idling();
	// Devuelve si la acción del jugador es movimiento, siempre se coprueba justo antes de idling
	virtual bool moving();

	// Devuelve si la animación actual es la de ataque
	inline bool playingAttack() {
		return isCurrentAnimation(CHARACTER_ATTACK_IDLE_KEY) && isPlaying();
	}

	// Si el jugador se mueve a la izquierda hace flip horizontal y viceversa
	void adjustDirection();
	// Asigna si se quiere que el sprite haga flip dependiendo de su dirección
	inline void setWantToAdjustDirection(bool want) {
		wantToAdjustDirection = want;
	}
};

