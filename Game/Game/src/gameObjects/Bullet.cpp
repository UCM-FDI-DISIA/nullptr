#include "Bullet.h"
#include "../core/SDLApplication.h"

Bullet::Bullet(Vector2D pos, Vector2D dir, int dmg, vector<GameObject*> target, SDLApplication* game, Transform* camera)
{
	addComponent<BulletBehavior>(dmg, target);
	addComponent<Transform>(pos, dir, 30, 30);
	addComponent<Image>(game->getTexture("Bullet"), camera);
	addComponent<ColliderComponent>();
}
Bullet::Bullet(Vector2D pos, Vector2D dir, int dmg, GameObject* target, SDLApplication* game, Transform* camera)
{
	addComponent<BulletBehavior>(dmg, target);
	addComponent<Transform>(pos, dir, 30, 30);
	addComponent<Image>(game->getTexture("Bullet"), camera);
	addComponent<ColliderComponent>();
}