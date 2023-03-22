#pragma once

#include "../utils/Singleton.h"
#include <unordered_map>

class CardsDataContainer : public Singleton<CardsDataContainer> {
	friend Singleton<CardsDataContainer>;
private:
	template <typename T>
	class dataContainer {
	private:
		unordered_map<std::string, T> dataMap;
	public:
		T at(std::string key) {
			return dataMap.at(key);
		}
	};
public:
};