#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Node Objects/NodeButton.h"

MapScene::MapScene() {
	// MAPA
	gameMap().reloadMap();
	vector<vector<Node*>> const& nodeMap = gameMap().getNodeMap();
	vector<int> const& nodesPerHeight = gameMap().getNodesPerWidth();

	// VECTOR PARA EL RENDERIZADO DE LAS CONEXIONES
	vector<vector<Vector2D>> nodesPositions(HEIGHT);

	int i = 0;
	for (auto& height : nodeMap) {
		int j = 0;
		for (Node* node : height) {
			Vector2D pos = Vector2D(0, (int)WIN_HEIGHT - NODE_POSITION_Y * i);
			if (node != nullptr) { 
				switch (nodesPerHeight[i]) {
				case 1:
					pos.setX(NODE_POSITIONS_X[2]);
					break;
				case 2:
					if (j == 0) pos.setX(NODE_POSITIONS_X[1]);
					else pos.setX(NODE_POSITIONS_X[3]);
					break;
				case 3:
					if (j == 0) pos.setX(NODE_POSITIONS_X[0]);
					else if (j == 1) pos.setX(NODE_POSITIONS_X[2]);
					else pos.setX(NODE_POSITIONS_X[4]);
					break;
				}
				addGameObject<NodeButton>(node, node->loadNode(), pos);
				++j;
			}
			nodesPositions[i].push_back(pos);
		}
		if (i > 0) createConections(nodeMap, nodesPositions, nodesPerHeight, i);
		++i;
	}

	camera->getComponent<Transform>()->setY((- (int)WIN_HEIGHT / 2) + NODE_HEIGHT);

	// BOTONES
	// Botón options
	createButton(MS_OPTIONS_BUTTON_POS, MS_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón Inventario
	createButton(MS_INVENTORY_BUTTON_POS, MS_INVENTORYFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<InventoryScene>(); }, INVENTORY)->setAsCurrentButton();

	// Botón salir
	createButton(MS_EXIT_BUTTON_POS, MS_EXITFRAME_BUTTON_POS, []() { SDLApplication::newScene<MainMenuScene>(); }, EXIT);
}

// Crear un bot�n especificado en la escena
Button* MapScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);
	// Crear marco
	GameObject* frame = addGameObject();
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols)->attachToCamera();

	// Crear bot�n
	return addGameObject<Button>(_cb, _bPos, aI, frame);
}

// Mueve la camara a la altura de los siguientes al nodo actual
void MapScene::moveCamera() {
	Transform* tr = camera->getComponent<Transform>();
	float prevY = tr->getY();
	tr->setY(prevY + NODE_POSITION_Y);
}

void MapScene::createConections(vector<vector<Node*>> const& nodes, vector<vector<Vector2D>> const& nodesPos, vector<int> const& nodesPerHeight, int alt) {
	int iIndNode = 0;
	for (int i = 0; i < nodes[alt - 1].size(); i++) {
		if (nodes[alt - 1][i] != nullptr) {
			int jIndNode = 0;
			for (int j = 0; j < nodes[alt].size(); ++j) {
				if (nodes[alt][j] != nullptr) {
					if (nodes[alt - 1][i]->conectsWith(j)) {
						GameObject* conection = addGameObject();
						string key = "";
						Vector2D pos = Vector2D(0, (int)WIN_HEIGHT - NODE_POSITION_Y * alt + NODE_HEIGHT);
						
						if (nodesPerHeight[alt - 1] == 1) {
							if (nodesPerHeight[alt] == 1) {
								/*conectar POS 2 con POS 2*/
								key = "StraightNodeConection";
								pos.setX(NODE_POSITIONS_X[2]);
							}
							else if (nodesPerHeight[alt] == 2) {
								if (jIndNode == 0) {
									/*conectar POS 2 con POS 1*/
									key = "ReverseMidNodeConection";
									pos.setX(NODE_POSITIONS_X[1]);
								}
								else /*if (jIndNode == 1)*/ {
									/*conectar POS 2 con POS 3*/
									key = "MidNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
							}
							else /*if (nodesPerHeight[alt] == 3)*/ {
								if (jIndNode == 0) {
									/*conectar POS 2 con POS 0*/
									key = "ReverseFarNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
								else if (jIndNode == 1) {
									/*conectar POS 2 con POS 2*/
									key = "StraightNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
								else /*if (jIndNode == 2)*/ {
									/*conectar POS 2 con POS 4*/
									key = "FarNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
							}
						}
						else if (nodesPerHeight[alt - 1] == 2) {
							if (iIndNode == 0) {
								if (nodesPerHeight[alt] == 1) {
									/*conectar POS 1 con POS 2*/
									key = "MidNodeConection";
									pos.setX(NODE_POSITIONS_X[1]);
								}
								else if (nodesPerHeight[alt] == 2) {
									if (jIndNode == 0) {
										/*conectar POS 1 con POS 1*/
										key = "StraightNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 1 con POS 3*/
										key = "FarNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
								}
								else /*if (nodesPerHeight[alt] == 3)*/ {
									if (jIndNode == 0) {
										/*conectar POS 1 con POS 0*/
										key = "ReverseMidNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									else if (jIndNode == 1) {
										/*conectar POS 1 con POS 2*/
										key = "MidNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
									else /*if (jIndNode == 2)*/ {
										/*conectar POS 1 con POS 4*/
										key = "LongNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
								}
							}
							else /*if (iIndNode == 1)*/ {
								if (nodesPerHeight[alt] == 1) {
									/*conectar POS 3 con POS 2*/
									key = "ReverseMidNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
								else if (nodesPerHeight[alt] == 2) {
									if (jIndNode == 0) {
										/*conectar POS 3 con POS 1*/
										key = "ReverseFarNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 3 con POS 3*/
										key = "StraightNodeConection";
										pos.setX(NODE_POSITIONS_X[3]);
									}
								}
								else /*if (nodesPerHeight[alt] == 3)*/ {
									if (jIndNode == 0) {
										/*conectar POS 3 con POS 0*/
										key = "ReverseLongNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									else if (jIndNode == 1) {
										/*conectar POS 3 con POS 2*/
										key = "ReverseMidNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
									}
									else /*if (jIndNode == 2)*/ {
										/*conectar POS 3 con POS 4*/
										key = "MidNodeConection";
										pos.setX(NODE_POSITIONS_X[3]);
									}
								}
							}
						}
						else /*if (nodesPerHeight[alt - 1] == 3)*/ {
							if (iIndNode == 0) {
								if (nodesPerHeight[alt] == 1) {
									/*conectar POS 0 con POS 2*/
									key = "FarNodeConection";
									pos.setX(NODE_POSITIONS_X[0]);
								}
								else if (nodesPerHeight[alt] == 2) {
									if (jIndNode == 0) {
										/*conectar POS 0 con POS 1*/
										key = "MidNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 0 con POS 3*/
										key = "LongNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
								}
								else /*if (nodesPerHeight[alt] == 3)*/ {
									if (jIndNode == 0) {
										/*conectar POS 0 con POS 0*/
										key = "StraightNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 0 con POS 2*/
										key = "FarNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									// CASO IMPOSIBLE
									// else /*if (jIndNode == 2)*/ {
									// 	/*conectar POS 0 con POS 4*/
									// }
								}
							}
							else if (iIndNode == 1) {
								if (nodesPerHeight[alt] == 1) {
									/*conectar POS 2 con POS 2*/
									key = "StraightNodeConection";
									pos.setX(NODE_POSITIONS_X[2]);
								}
								else if (nodesPerHeight[alt] == 2) {
									if (jIndNode == 0) {
										/*conectar POS 2 con POS 1*/
										key = "ReverseMidNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 2 con POS 3*/
										key = "MidNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
									}
								}
								else /*if (nodesPerHeight[alt] == 3)*/ {
									if (jIndNode == 0) {
										/*conectar POS 2 con POS 0*/
										key = "ReverseFarNodeConection";
										pos.setX(NODE_POSITIONS_X[0]);
									}
									else if (jIndNode == 1) {
										/*conectar POS 2 con POS 2*/
										key = "StraightNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
									}
									else /*if (jIndNode == 2)*/ {
										/*conectar POS 2 con POS 4*/
										key = "FarNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
									}
								}
							}
							else /*if (iIndNode == 2)*/ {
								if (nodesPerHeight[alt] == 1) {
									/*conectar POS 4 con POS 2*/
									key = "ReverseFarNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
								}
								else if (nodesPerHeight[alt] == 2) {
									if (jIndNode == 0) {
										/*conectar POS 4 con POS 1*/
										key = "ReverseLongNodeConection";
										pos.setX(NODE_POSITIONS_X[1]);
									}
									else /*if (jIndNode == 1)*/ {
										/*conectar POS 4 con POS 3*/
										key = "ReverseMidNodeConection";
										pos.setX(NODE_POSITIONS_X[3]);
									}
								}
								else /*if (nodesPerHeight[alt] == 3)*/ {
									// CASO IMPOSIBLE
									// if (jIndNode == 0) {
									// 	/*conectar POS 4 con POS 0*/
									// }
									/*else */if (jIndNode == 1) {
										/*conectar POS 4 con POS 2*/
										key = "ReverseFarNodeConection";
										pos.setX(NODE_POSITIONS_X[2]);
									}
									else /*if (jIndNode == 2)*/ {
										/*conectar POS 4 con POS 4*/
										key = "StraightNodeConection";
										pos.setX(NODE_POSITIONS_X[4]);
									}
								}
							}
						}
						float w;
						if (key == "StraightNodeConection") w = 6;
						else if (key == "MidNodeConection" || key == "ReverseMidNodeConection") w = 213;
						else if (key == "FarNodeConection" || key == "ReverseFarNodeConection") w = 427;
						else w = 640;

						pos.setX(pos.getX() + CONECTION_OFFSET);
						conection->addComponent<Transform>(pos, VECTOR_ZERO, w, NODE_DISTANCE);
						conection->addComponent<Image>(&sdlutils().images().at(key));
					}
					++jIndNode;
				}
			}
			++iIndNode;
		}		
	}
}
