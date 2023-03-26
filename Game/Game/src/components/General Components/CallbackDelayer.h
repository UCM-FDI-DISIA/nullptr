#pragma once
#include "../../gameObjects/GameObject.h"
#include "../Component.h"


class CallbackDelayer : public Component
{
private:

	double timer = 0.0;
	double requestedDelay;
	CallBack callback;
public:
	static const int id = _CALLBACK_DELAYER;

	CallbackDelayer(CallBack cb, double delay_ms) :callback(cb), requestedDelay(delay_ms) {};

	virtual void initComponent() {}

	virtual void update();

};
