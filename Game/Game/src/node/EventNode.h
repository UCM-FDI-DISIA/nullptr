#pragma once
#ifndef EVENTNODE_H_
#define EVENTNODE_H_

#include "Node.h"

class EventNode : public Node {
private:
public:
	EventNode();
	virtual CallBack* loadNode() const;
};

#endif // !EVENTNODE_H_
