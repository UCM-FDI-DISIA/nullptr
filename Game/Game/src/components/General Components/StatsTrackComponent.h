#pragma once
#include "../Component.h"
/*
Objeto que se encarga de hacer un seguimiento
de las diferentes estadísticas del rendimiento
del jugador durante la patida
*/


class StatsTrackComponent : public Component {
private:
	//Para agregar los enemigos a la escena de combate
	int damage, melee, ranged, tank, money;
	float time;

	bool timeCounting;

	void calculateMoney();

public:
	static const int id = _STATS_TRACK;
	StatsTrackComponent() : damage(0), melee(0), ranged(0), tank(0), money(0), time(0), timeCounting(true) {}


	virtual void update();

	void onPlayerDamage(int dmg);
	void onEnemyKilled(GameObject* enemy);
	void endTimeCouinting();
	void startStatsScene();



};