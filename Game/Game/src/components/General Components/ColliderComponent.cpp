#include "ColliderComponent.h"
#include "../../scenes/GameState.h"
#include "../../core/SDLApplication.h"


// Recibe una funci�n a realizar cuando los objetos chocan y una lista de objetos con los que chocan
ColliderComponent::ColliderComponent(grpId id)
{
	target = id;
	width = 0;
	height = 0;
	tr = nullptr;
}

ColliderComponent::ColliderComponent(grpId id, int w, int h)
{
	target = id;
	width = w;
	height = h;
	tr = nullptr;
}

void ColliderComponent::initComponent()
{
	tr = gObj->getComponent<Transform>();
	assert(tr != nullptr);
	if (width == 0) width = tr->getWidth();
	if (height == 0) height = tr->getHeight();
}


void ColliderComponent::update()
{
	if (functions.size() > 0) hasCollided();
}

void ColliderComponent::addFunction(CallBackCol function) {
	functions.push_back(function);
}

void ColliderComponent::addFunction(CallBackExpl function) {
	otherfncts.push_back(function);
}

// Comprueba la colisi�n del objeto con la lista de colisionados
void ColliderComponent::hasCollided() {
	//Sacamos todos los par�metros del transform propio
	Vector2D pos1 = getPos();
	float width1 = getWidth();
	float height1 = getHeight();
	float rot1 = getRotation();
	Vector2D anch1 = getAnchorPoint();
	vector<GameObject*> const& others = gStt->getEntitiesByGroup(target);
	//Por cada gameObject dentro del grupo correspondiente sacamos los par�metros de su transform
	for (GameObject* other : others) {
		ColliderComponent* otherCl = other->getComponent<ColliderComponent>();
		if (otherCl != nullptr) {
			Vector2D pos2 = otherCl->getPos();
			float width2 = otherCl->getWidth();
			float height2 = otherCl->getHeight();
			float rot2 = otherCl->getRotation();
			Vector2D anch2 = otherCl->getAnchorPoint();
			//Se comprueba si colisionan utilizando los par�metros previamente obtenidos
			if (Collisions::collidesWithRotation(pos1, width1, height1, rot1, anch1,
				pos2, width2, height2, rot2, anch2))
			{
				// Si colisiona, realiza la funci�n
				for (CallBackCol function : functions) function(other);
			}
		}
	}
}

Vector2D ColliderComponent::getPos()
{
	return tr->getCenter() - Vector2D(width / 2, height / 2);
}

float ColliderComponent::getWidth()
{
	return width;
}

float ColliderComponent::getHeight()
{
	return height;
}

float ColliderComponent::getRotation()
{
	return tr->getRotation();
}

Vector2D ColliderComponent::getAnchorPoint()
{
	Vector2D newAnch = tr->getAnchorPoint();
	newAnch.setX((newAnch.getX() / tr->getWidth()) * width);
	newAnch.setY((newAnch.getY() / tr->getHeight()) * height);
	return newAnch;
}

#ifdef _DEBUG
void ColliderComponent::render() const{
	SDL_Rect rect;
	rect.x = (tr->getCenter() - Vector2D(width / 2, height / 2)).getX() + gStt->getCamera()->getComponent<Transform>()->getRect().x;
	rect.y = (tr->getCenter() - Vector2D(width / 2, height / 2)).getY() + gStt->getCamera()->getComponent<Transform>()->getRect().y;
	rect.w = width;
	rect.h = height;

	SDL_Point* anch = new SDL_Point;
	anch->x = (tr->getAnchorPoint().getX() / tr->getWidth()) * width;
	anch->y = (tr->getAnchorPoint().getY() / tr->getHeight()) * height;

	Texture* texture = SDLApplication::getTexture("Collider");

	texture->render(rect, tr->getRotation(), anch);

	delete anch;
}
#endif

