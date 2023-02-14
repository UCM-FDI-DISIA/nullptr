#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <array>
#include <vector>
#include "../components/Component.h"
#include "../data/constants.h"

using namespace std;

class GameObject {
private:
	bool alive;
	Manager* mngr;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;
public:
	// Constructor
	GameObject() : mngr(nullptr), cmps(), currCmps(), alive(true) {
		currCmps.reserve(maxComponentId);
	}
	// Destructor
	virtual ~GameObject() { 
		for (Component* cmp : currCmps) {
			delete cmp;
			cmp = nullptr;
		}
		for (Component* cpm : cmps) {
			cpm = nullptr;
		}
	}
	// Asigna el Manager del GameObject
	inline void setContext(Manager* _mngr) { mngr = _mngr; }
	// Devuelve si el GameObject está vivo
	inline bool isAlive() { return alive; }
	// Asigna si el GameObject está vivo o no
	inline void setAlive(bool _alive) { alive = _alive; }
	// Añade el Component dicho al GameObject, devuelve un puntero a ese Component
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
	// Elimina el Component dicho del GameObject
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
	// Devuelve el Compoment pedido del GameObject
	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(cmps[T::id]);
	}
	// Devuelve si el GameObject tiene el Component pedido
	template<typename T>
	inline bool hasComponent() {
		return cmps[T::id] != nullptr;
	}
	// Actualiza el GameObject
	virtual void update() {
		for (Component* cmp : currCmps) {
			cmp->update();
		}
	}
	// Dibuja el GameObject en pantalla
	virtual void render() const {
		for (Component* cmp : currCmps) {
			cmp->render();
		}
	}
	// Maneja los eventos del GameObject
	virtual void handleInput() {
		for (Component* cmp : currCmps) {
			cmp->handleInput();
		}
	}
};
#endif
