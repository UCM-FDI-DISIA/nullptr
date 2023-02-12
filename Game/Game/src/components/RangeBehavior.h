#pragma once
#include "EnemyBehavior.h"

// Esta clase define el comportamiento del enemigo a distancia
// Se mueve por un tiempo determinado y se queda parado otro
class RangeBehavior :public EnemyBehavior
{
private:
	float safeDistance = 0;
	Vector2D initialDir;
	float stopTime = 0;
	float moveTime = 0;
	float elapsedTime = 0;
	float actualTime = 0;
	bool stopped = false;
public:
	static const int id = _RANGE_BEHAVIOR;
	RangeBehavior(float spd, float safDist, float stoptime, float moveTime);
	virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	virtual void attack();
};

