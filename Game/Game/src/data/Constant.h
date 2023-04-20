#pragma once
#include <unordered_map>
#include <string>
#include "json/JSON.h"
#include "constants.h"
#include "../utils/Singleton.h"
using namespace std;

class Constant : public Singleton<Constant> {
private:
	friend Singleton<Constant>;

	static unordered_map<string, double> numberCts_;

public:
	static unordered_map<string, double> getNumbersFromJSON();

	static inline int getInt(const string& key) {
		return (int)numberCts_.at(key);
	}

	static inline float getFloat(const string& key) {
		return (float)numberCts_.at(key);
	}

	static inline double getDouble(const string& key) {
		return numberCts_.at(key);
	}
};



