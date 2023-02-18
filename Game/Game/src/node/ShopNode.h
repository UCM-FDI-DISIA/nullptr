#pragma once
#ifndef SHOPNODE_H_
#define SHOPNODE_H_

#include "Node.h"
class ShopScene;

class ShopNode : public Node {
public:
	ShopNode();
	virtual void loadNode() const;
};

#endif // !SHOPNODE_H_
