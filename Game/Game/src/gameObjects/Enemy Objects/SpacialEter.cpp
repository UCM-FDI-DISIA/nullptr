#include "SpacialEter.h"
void SpacialEter::initGameObject(int x, int y, Transform* player)
{
	addComponent<Transform>(Vector2D(x,y), Vector2D(), Constant::getInt("ETHER_W"), Constant::getInt("ETHER_H"), 0);
	addComponent<EterBehaviour>(3000, player);
	addComponent<Image>(SDLApplication::getTexture("Eter"));
}