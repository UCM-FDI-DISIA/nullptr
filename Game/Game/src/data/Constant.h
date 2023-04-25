#pragma once
#include <unordered_map>
#include <string>
#include "json/JSON.h"
#include "constants.h"
#include "../utils/Singleton.h"
#include "../core/Vector2D.h"
#include "../components/ecs.h"
using namespace std;
using TextureName = string;

class Constant : public Singleton<Constant> {
private:
	friend Singleton<Constant>;

	static unordered_map<string, double> numberCts_;
	static unordered_map<string, string> stringCts_;
	static unordered_map<string, Vector2D> vectorCts_;
	static unordered_map<string, Animation> animationCts_;

public:
	static void loadConstantsFromJSON();

	static inline int getInt(const string& key) {
		return (int)numberCts_.at(key);
	}

	static inline float getFloat(const string& key) {
		return (float)numberCts_.at(key);
	}

	static inline double getDouble(const string& key) {
		return numberCts_.at(key);
	}

	static inline string getString(const string& key) {
		return stringCts_.at(key);
	}

	static inline TextureName getTextureName(const string& key) {
		return stringCts_.at(key);
	}

	static inline Vector2D getVector2D(const string& key) {
		return vectorCts_.at(key);
	}

	static inline Animation getAnimation(const string& key) {
		return animationCts_.at(key);
	}
};



