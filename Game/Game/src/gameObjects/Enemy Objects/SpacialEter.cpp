#include "SpacialEter.h"
void SpacialEter::initGameObject(int x, int y, Transform* player)
{
	addComponent<Transform>(Vector2D(x,y), VECTOR_ZERO, ETHER_W, ETHER_H, 0);
	addComponent<EterBehaviour>(3000, player);
	addComponent<Image>(SDLApplication::getTexture("Eter"));
}