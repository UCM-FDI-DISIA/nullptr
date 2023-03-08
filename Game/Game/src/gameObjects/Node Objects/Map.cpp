#include "Map.h"
#include "../../data/json/JSON.h"

Map::Map() : nodeMap(unordered_map<string, Node*>()), initialNodes(vector<Node*>()), unlockedNodes(initialNodes), currentNode(nullptr) {
	// Crear el mapa de nodos
	// Crear los nodos (con unos iniciales desbloqueados)
	
	initMap("../Game/src/data/game.map.json");
}

Map::~Map() {
	// Borrar el mapa de nodos
	for (auto& node : nodeMap) {
		delete node.second;
		node.second = nullptr;
	}
}

void Map::initMap(string filename) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	unordered_map<string, JSONArray> nexts;

	// load fonts
	jValue = root["map"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			nodeMap.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string name = vObj["name"]->AsString();
					std::string type = vObj["type"]->AsString();
					int height = static_cast<int>(vObj["height"]->AsNumber());
					JSONArray next = vObj["next"]->AsArray();
#ifdef _DEBUG
					std::cout << "Loading node with id: " << name << std::endl;
#endif
					Node* n = addNode(type, name, NODE_POSITIONS[height]);
					nexts[name] = next;

				} else {
					throw "'node' array in '" + filename
							+ "' includes and invalid value";
				}
			}

			for (auto next : nexts) {
				for (auto a : next.second) {
					nodeMap[next.first]->addToNextNodes(nodeMap[a->AsString()]);
				}
			}
			
		} else {
			throw "'node' is not an array in '" + filename + "'";
		}
	}
}

void Map::setCurrentNode(Node* node) {
	currentNode = node;
}

void Map::completeCurrentNode() {
	currentNode->complete(unlockedNodes);
}