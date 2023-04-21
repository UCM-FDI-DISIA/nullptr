#pragma once
#include "../../utils/Singleton.h"
#include "Node.h"
#include <unordered_map>

class Map : public Singleton<Map> {
	friend Singleton<Map>;
private:
	// Mapa de todos los nodos
	vector<vector<Node*>> nodeMap;
	vector<Node*> initialNodes;
	vector<Node*>& unlockedNodes;
	Node* currentNode; // Nodo actual

	vector<int> nodesPerHeight;

	string nodeTextureKeys[NodeType::None];
	function<void(BattleType)> nodeLoads[NodeType::None];

	// Constructora
	Map();

	// Inicializa el array de claves de las texturas de los nodos
	void initTextureKeys();
	// Inicializa el array de CallBacks de los nodos
	void initNodeLoads();
	// Inicializa el mapa de nodos a partir de un JSON
	void initMap(string filename);
	// Crea el mapa
	void createMap();

	// Limpia el mapa
	void clearMap();
	
	// Hay ciertos nodos que son compatibles bajo unas condiciones, este m�todo tiene una probabilidad de juntar dos nodos que cumplan esas condiciones
	void lookForCompatibles(Needs& n1, Needs& n2);
	// Recibe las condiciones con las que se cre� un nodo y devuelve las condiciones que necesita para su siguiente nodo
	Needs getNeed(Needs prevNeed);
	// Recibe un vector de nodos y devuelve un vector con las condiciones para crear su siguiente altura
	vector<Needs> getNeeds(vector<Node*> const& nodes);

	// Evita cruces entre conexiones de nodos
	bool validConection(vector<vector<Node*>> m, int alt, int i, int j);
	// Comprueba si un nodo puede tener a otro como siguiente, recibe sus condiciones de creaci�n
	bool linkableNodes(Needs prev, Needs next);
	// Inicializa enteros que se usar�n para recorrer de izq a der o al reves
	void getRandomWay(int& start, int& end, int& sum);
	// Recorre la altura anterior a la indicada para buscar nodos anteriores a aquel con el �ndice pasado
	bool lookForPrevious(vector<vector<Node*>> m, int alt, int ind);
	// Genera los nodos en la altura indicada, se llama recursivamente hasta llegar al final del arbol
	void generateLevel(vector<vector<Node*>>& m, int maxHeight, int k);
	// A�ade un nodo al mapa en la posici�n indicada con las condiciones indicadas
	Node* addNode(int height, int pos, Needs n, BattleType bt = BattleType(rand() % _NONE));
	// Borra el nodo en la posici�n dada
	void eraseNode(int height, int pos);
public:
	// Destructora
	~Map();
	// Asigna el nodo actual
	void setCurrentNode(Node* node);
	// Devuelve el nodo actual
	inline Node* getCurrentNode() { return currentNode; }
	// Completa el nodo actual
	void completeCurrentNode();
	// Devuelve una referencia constante al mapa de nodos
	inline vector<vector<Node*>> const& getNodeMap() { return nodeMap; }
	// Devuelve una referencia constante al mapa de nodos
	inline vector<int> const& getNodesPerWidth() { return nodesPerHeight; }
	// Borra el mapa actual y crea uno nuevo
	void reloadMap();
};
// Referencia a la instancia del mapa
inline Map& gameMap() { return *Map::instance(); }