#pragma once
#include "../core/GameObject.h"
#include "../components/Transform.h"
#include "../components/ColliderComponent.h"
#include "../components/BulletBehavior.h"


class SDLApplication;
class Bullet:public GameObject
{
public:
	// Se le pasa la posición de inicio de quien lo ha disparado y la dirección a la que va

	Bullet(Vector2D pos, Vector2D dir, int dmg, vector<GameObject*> target, SDLApplication* game, Transform* camera);
	Bullet(Vector2D pos, Vector2D dir, int dmg, GameObject* target, SDLApplication* game, Transform* camera);
};
