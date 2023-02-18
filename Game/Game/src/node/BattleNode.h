#pragma once
#ifndef BATTLENODE_H_
#define BATTLENODE_H_

#include "Node.h"
class BattleScene;

enum battleType {
	_PASTBATTLE = 0,
	_PRESENTBATTLE,
	_FUTUREBATTLE
};

class BattleNode : public Node {
private:
	battleType type;
public:
	BattleNode();
	virtual void loadNode() const;
};

#endif // !BATTLENODE_H_
