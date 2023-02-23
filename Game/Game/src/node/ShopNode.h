#pragma once
#ifndef SHOPNODE_H_
#define SHOPNODE_H_

#include "Node.h"
class ShopScene;

class ShopNode : public Node {
	friend Node;
private:
	ShopNode(Vector2D const& pos);
public:
	virtual CallBack loadNode() const;
};

#endif // !SHOPNODE_H_
