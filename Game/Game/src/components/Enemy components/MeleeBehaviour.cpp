#include "MeleeBehaviour.h"
#include "../../core/SDLApplication.h"
#include "../../gameObjects/Card Objects/Hitbox.h"

MeleeBehaviour::MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player) :EnemyBehaviour(spd, dmg, stopT, attack, player) {
	attackDistance = atkDist;
}

//Inicializacion de variables necesarias para el componente
void MeleeBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0, speed));
	initialDir = pos->getVel();
	pos->lookAt(playerPos->getPos());
	hasBeenCloseToPlayer = false;
	attacked = false;
	attacking = false;
	elapsedTime = SDL_GetTicks();
	gObj->getComponent<ColliderComponent>()->addFunction(meleeAttack());
	playerLife = player->getComponent<HealthComponent>();
}


//Metodo para saber si el enemigo esta cerca del player
void MeleeBehaviour::close() {
	// Si está cerca del jugador
	if (pos->getDistance(playerPos->getPos()) < attackDistance) {
		// Si no ha estado cerca del jugador antes
		if (!hasBeenCloseToPlayer) {
			// Llama al callback meleeAttack() aquí
			
				meleeAttack()(gObj);
			// Configura elapsedTime, velocidad a 0 y marca que ha estado cerca del jugador ya
			behaviorTime = SDLApplication::instance()->getCurrentTime() + stopTime;
			pos->setVel(Vector2D(0, 0));
			hasBeenCloseToPlayer = true;
			attacking = true;
			attacked = true;
		}
	}
}


void MeleeBehaviour::update() {
	attacking = false;
	if (confused) {
		pos->setVel(Vector2D(rand(), rand()).normalize() * speed);
	}
	else {
		elapsedTime += SDLApplication::instance()->getDeltaTime();
		close();
		if (hasBeenCloseToPlayer) {
			// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
			if (elapsedTime >= behaviorTime) {
				pos->setVel(initialDir);
				hasBeenCloseToPlayer = false;
			}
		}

		//Si ha pasado suficiente tiempo para atacar
		else if (elapsedTime >= attackInterval)
		{
			attacked = false;

			//Reseteamos el contador
			behaviorTime -= attackInterval;
		}

		pos->lookAt(playerPos->getPos());
	}
}

// Funci�n a realizar en colision
CallBackCol MeleeBehaviour::meleeAttack()
{
	return [&](GameObject* gameObject)
	{
		attacking = true;
		attacked = true;
		enemyAttack();
		//Da�a al jugador e informa de que ha atacado
	};
}

void MeleeBehaviour::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0 && playerLife->getInvencibility() <= 0) {
		vel = vel / vel.magnitude();
		Vector2D attackPos = pos->getPos() + vel * 100;
		float rotation = Vector2D(1, 0).angle(vel);
		Hitbox::HitboxData data = { attackPos, VECTOR_ZERO, rotation, 200, 100, "NewSwordSpin", _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, 0.1, data, Vector2D(-1,-1),nullptr, gObj->getComponent<Transform>()->getPos());
		//player->getComponent<HealthComponent>()->receiveDamage(0);
		cout << "hitbox" << endl;
	}
}

