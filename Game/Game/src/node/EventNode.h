#pragma once
#ifndef EVENTNODE_H_
#define EVENTNODE_H_

#include "Node.h"

class EventNode : public Node {
	friend Node;
private:
	EventNode(Vector2D const& pos);
public:
	virtual CallBack* loadNode() const;
};

#endif // !EVENTNODE_H_
