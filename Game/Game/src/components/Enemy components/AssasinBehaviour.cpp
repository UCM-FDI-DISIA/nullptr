#include "AssasinBehaviour.h"
#include "../../core/SDLApplication.h"
#include "../../gameObjects/Card Objects/Hitbox.h"

AssasinBehaviour::AssasinBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player) :EnemyBehaviour(spd, dmg, stopT, attack, player) {
	safeDistance = atkDist;
	dashTime = attack;
	elapsedDash = 0;
	elapsedTime = 0;
}

void AssasinBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0, speed));
	initialDir = pos->getVel();
	pos->lookAt(playerPos->getPos());
	hasBeenCloseToPlayer = false;
	attacked = false;
	attacking = false;
	elapsedTime = SDL_GetTicks();
	gObj->getComponent<ColliderComponent>()->addFunction(assasinAttack());
}

bool AssasinBehaviour::close() {
	//Si esta cerca del player
	if (pos->getDistance(playerPos->getPos()) < safeDistance) {
		return true;
	}
	else return false;
}

void AssasinBehaviour::update() {

	//Cuando bala cerca queremos dash
	//Cuando jugador cerca queremos dash hacia el jugador
	//Si el dash esta en cooldown no se

	attacking = false;
	if (confused) {
		pos->setVel(Vector2D(rand(), rand()).normalize() * speed);
	}
	else {
		elapsedTime += SDLApplication::instance()->getDeltaTime();
		if(attacked) elapsedDash += SDLApplication::instance()->getDeltaTime();
		if (elapsedDash >= dashTime && attacked){
			elapsedDash = 0;
			attacked = false;
			pos->setVel(Vector2D(0, 1.2 * ENEMY_SPEED));
		}
		close();
		if(!attacked){
			pos->lookAt(playerPos->getPos());
		}
	}
	
	 if (elapsedTime >= dashCooldown) {
		 if (!attacked && close()) {
			 attacked = true;
			 dash(true);
		 }
		 else if(!attacked) {
			 auto bullets = gStt->getEntitiesByGroup(_grp_PLYR_ATTACK);
			 for (auto& bullet : bullets) {
				 Transform* bulletTransform = bullet->getComponent<Transform>();
				 if (pos->getDistance(bulletTransform->getPos()) < safeDistance)
				 {
					 attacked = true;
					 dash(false);
					 elapsedTime = 0;
					 elapsedDash = 0;
				 }
			 }
		 }

	 }
}

// Funci�n a realizar en colision
CallBackCol AssasinBehaviour::assasinAttack()
{
	return [&](GameObject* gameObject)
	{
		enemyAttack();
		//Da�a al jugador e informa de que ha atacado


	};
}



void AssasinBehaviour::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel / vel.magnitude();
		Vector2D attackPos = pos->getPos() + vel * 100;
		float rotation = Vector2D(1, 0).angle(vel);
		Hitbox::HitboxData data = { attackPos, VECTOR_ZERO, rotation, 200, 100, "null", _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, 10, data, Vector2D(-1, -1), nullptr, gObj->getComponent<Transform>()->getPos());
		//player->getComponent<HealthComponent>()->receiveDamage(0);
	}
}

void AssasinBehaviour::dash(bool atacking)
{
	Vector2D dashDir;
	if(!atacking)dashDir= pos->getVel().rotate(SDLApplication::instance()->getRandInt(0, 2) ? 70 : -70) * 10;
	else {
		pos->lookAt(player->getComponent<Transform>()->getPos());
		dashDir = pos->getVel() * 10;
	}
	pos->setVel(dashDir);
}
