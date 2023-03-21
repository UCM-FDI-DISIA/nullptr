#include "ChestComponent.h"

void ChestComponent::initComponent() {
	spawnPos = gObj->getComponent<Transform>();
}

