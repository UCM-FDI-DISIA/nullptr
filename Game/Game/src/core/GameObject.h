#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <array>
#include <vector>
#include "../components/Component.h"

#include <iostream>
using namespace std;

class GameObject {
private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;
public:
	// Destructor
	virtual ~GameObject(){}
	// Sets the manager of the GameObject
	inline void setContext(Manager* _mngr) { mngr = _mngr; }
	// Returns whether the GameObject is alive or not
	inline bool isAlive() { return alive; }
	// Sets whether the GameObject is alive or not
	inline void setAlive(bool _alive) { alive = _alive; }
	// Adds said component to the GameObject
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();
		currCmps.push_back(c);
		cmps[T::id] = c;
		c->setContext(this, mngr);
		c->initComponent();
		return c;
	}
	// Removes said component from the GameObject
	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;

		if (cmps[cId] != nullptr) {
			auto iter = std::find(currCmps.begin(),
				currCmps.end(),
				cmps[cId]);
			currCmps.erase(iter);
			delete cmps[cId];
			cmps[cId] = nullptr;
		}
	}
	// Returns GameObject's asked component
	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(cmps[T::id]);
	}
	// Returns whether the GameObject has the asked component
	template<typename T>
	inline bool hasComponent() {
		return cmps[T::id] != nullptr;
	}
	// Updates the GameObject
	virtual void update() {
		for (Component* cmp : currCmps) {
			cmp->update();
		}
	}
	// Draws the GameObject on screen
	virtual void render() {
		for (Component* cmp : currCmps) {
			cmp->render();
		}
	}
	// Handle's the GameObject's events
	virtual void handleEvent(SDL_Event event) {
		for (Component* cmp : currCmps) {
			cmp->handleEvent(event);
		}
	}
};
#endif
