#include "Constant.h"

unordered_map<string, double> Constant::numberCts_;
unordered_map<string, string> Constant::stringCts_;
unordered_map<string, Vector2D> Constant::vectorCts_;

void Constant::loadConstantsFromJSON() {
	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(CONSTANTS_JSON_ROOT));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + CONSTANTS_JSON_ROOT + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	// load number constants
	jValue = root["number"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			numberCts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					double value = vObj["value"]->AsNumber();
#ifdef _DEBUG
					std::cout << "Loading number (int, float, double) info with id: " << key << std::endl;
#endif
					numberCts_.emplace(key, value);
				}
				else {
					throw "'number' array in '" + CONSTANTS_JSON_ROOT
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'number' is not an array in '" + CONSTANTS_JSON_ROOT + "'";
		}
	}

	// load number constants
	jValue = root["string"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			stringCts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string value = vObj["value"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading string info with id: " << key << std::endl;
#endif
					stringCts_.emplace(key, value);
				}
				else {
					throw "'string' array in '" + CONSTANTS_JSON_ROOT
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'string' is not an array in '" + CONSTANTS_JSON_ROOT + "'";
		}
	}

	// load vector constants
	jValue = root["vector"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			vectorCts_.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					float x = (float)vObj["x"]->AsNumber();
					float y = (float)vObj["y"]->AsNumber();
#ifdef _DEBUG
					std::cout << "Loading vector info with id: " << key << std::endl;
#endif
					
					vectorCts_.emplace(key, Vector2D(x,y));
				}
				else {
					throw "'vector' array in '" + CONSTANTS_JSON_ROOT
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'vector' is not an array in '" + CONSTANTS_JSON_ROOT + "'";
		}
	}
}