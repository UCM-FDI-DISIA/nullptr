#pragma once
#ifndef CHESTNODE_H_
#define CHESTNODE_H_

#include "Node.h"
class ChestScene;

class ChestNode : public Node {
public:
	ChestNode();
	virtual CallBack* loadNode() const;
};

#endif // !CHESTNODE_H_
