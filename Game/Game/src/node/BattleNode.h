#pragma once
#ifndef BATTLENODE_H_
#define BATTLENODE_H_

#include "Node.h"
#include "../core/SDLApplication.h"
class BattleScene;

enum battleType {
	_PASTBATTLE = 0,
	_PRESENTBATTLE,
	_FUTUREBATTLE
};

struct A : Singleton<A> {
	battleType type;
	CallBack* operator()(battleType t) {
		type = t;
		return (CallBack*)(A::instance());
	}
	void operator()(SDLApplication* game) {
		SDLApplication::newScene<BattleScene>(game, type);
	}
};

class BattleNode : public Node {
	friend Node;
private:
	battleType type;
	BattleNode(Vector2D const& pos);
public:
	virtual CallBack* loadNode() const;
};

#endif // !BATTLENODE_H_
