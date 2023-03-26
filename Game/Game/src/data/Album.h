#pragma once
#include "../utils/Singleton.h"

class Album : public Singleton<Album> {
	friend Singleton<Album>;
private:
	Album();
	void loadFromJSON();
	void saveToJSON();
public:
	virtual ~Album();
};