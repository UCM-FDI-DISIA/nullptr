#include"ColliderComponent.h"
#include "../../scenes/GameState.h"
// Recibe una función a realizar cuando los objetos chocan y una lista de objetos con los que chocan
ColliderComponent::ColliderComponent(grpId id)
{
	target = id;
}

void ColliderComponent::update()
{
	hasCollided();
}

void ColliderComponent::addFunction(CallBackCol function) {
	functions.push_back(function);
}

// Comprueba la colisión del objeto con la lista de colisionados
void ColliderComponent::hasCollided() {
	//Sacamos todos los parámetros del transform propio
	Transform* tr = gObj->getComponent<Transform>();
	Vector2D& pos1 = tr->getPos();
	float width1 = tr->getWidth();
	float height1 = tr->getHeight();
	float rot1 = tr->getRotation();
	Vector2D anch1 = tr->getAnchorPoint();
	vector<GameObject*> others = gStt->getEntitiesByGroup(target);
	//Por cada gameObject dentro del grupo correspondiente sacamos los parámetros de su transform
	for (GameObject* other : others) {
		Transform* otherTr = other->getComponent<Transform>();
		Vector2D& pos2 = otherTr->getPos();
		float width2 = otherTr->getWidth();
		float height2 = otherTr->getHeight();
		float rot2 = otherTr->getRotation();
		Vector2D anch2 = otherTr->getAnchorPoint();
		//Se comprueba si colisionan utilizando los parámetros previamente obtenidos
		if (Collisions::collidesWithRotation(pos1, width1, height1, rot1, anch1,
											 pos2, width2, height2, rot2, anch2))
		{
			// Si colisiona, realiza la función
			for(CallBackCol function : functions) function;

		}
	}
}