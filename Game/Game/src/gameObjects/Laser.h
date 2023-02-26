#include "../core/GameObject.h"
#include "../core/SDLApplication.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/BulletBehavior.h"
#include "../components/LifeTimeComponent.h"

class Laser : public GameObject {
public:
	void initGameObject(Vector2D pos, float rotation, int damage, vector<GameObject*>* enemies) {
		addComponent<Transform>(pos, Vector2D(0,0), WIDTH, HEIGHT, rotation)->setAnchorPoint(0, HEIGHT / 2);
		addComponent<Image>(SDLApplication::getTexture("Laser"));
		addComponent<BulletBehavior>(damage, enemies);
		addComponent<ColliderComponent>();
		addComponent<LifeTimeComponent>(0.25);
	}
private:
	const float HEIGHT = 10;
	const float WIDTH = 1100;
};