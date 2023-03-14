#include "SpacialEter.h"
void SpacialEter::initGameObject(int x, int y, Transform* player)
{
	addComponent<Transform>(Vector2D(x,y), Vector2D(0, 0), RANGED_ENEMY_WIDTH, RANGED_ENEMY_HEIGHT, 0);
	addComponent<EterBehaviour>(3000, player);
	addComponent<Image>(SDLApplication::getTexture("Eter"));
}