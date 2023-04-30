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
			Vector2D pos = Vector2D(0, (int)WIN_HEIGHT - NODE_POSITION_Y * (i + 3));
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
				addGameObject<NodeButton>(node, node->loadNode(), pos, (nodesPerHeight[i] == 1) ? 8.0f : 5.0f,
					[&](Transform* myTr) {
						camTr->setY(-myTr->getY() + sdlutils().height() / 2 - NODE_HEIGHT / 2);
					});
				++j;
			}
			nodesPositions[i].push_back(pos);
		}
		if (i > 0) createConections(nodeMap, nodesPositions, nodesPerHeight, i);
		++i;
	}

	camTr = camera->getComponent<Transform>();
	camTr->setY((- (int)WIN_HEIGHT / 2) + NODE_HEIGHT);
	camYLimit = -nodesPositions[nodesPositions.size() - 1][nodesPositions[nodesPositions.size() - 1].size() - 1].getY() + sdlutils().height() / 2;

	// BOTONES
	// Botón options
	createButton(MS_OPTIONS_BUTTON_POS, MS_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón Inventario
	inventoryButton = createButton(MS_INVENTORY_BUTTON_POS, MS_INVENTORYFRAME_BUTTON_POS, []() { SDLApplication::pushNewScene<InventoryScene>(); }, INVENTORY);
	inventoryButton->setAsDefaultButton();

	// Botón salir
	exitButton = createButton(MS_EXIT_BUTTON_POS, MS_EXITFRAME_BUTTON_POS, []() { SDLApplication::newScene<MainMenuScene>(); }, EXIT);
	
	
	auto animator = addGameObject<Button>([n = nodeMap[0][1]]() { gameMap().setCurrentNode(n); SDLApplication::pushNewScene<ChestScene>(); }, MM_EXIT_BUTTON_POS, AnimatorInfo(CHEST_NODE_TEXTURE_KEY, NODE_WIDTH, NODE_HEIGHT, NODE_FRAME_WIDTH, NODE_FRAME_HEIGHT, NODE_FRAME_ROWS, NODE_FRAME_COLUMNS))->getComponent<Animator>();
	animator->createAnim(ONOUT, NODE_BUTTON_ONOUT_START_FRAME, NODE_BUTTON_ONOUT_END_FRAME, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONOVER, NODE_BUTTON_ONOVER_START_FRAME, NODE_BUTTON_ONOVER_END_FRAME, ONOVER_SPEED, 1);
	animator->createAnim(ONCLICK, NODE_BUTTON_ONCLICK_START_FRAME, NODE_BUTTON_ONCLICK_END_FRAME, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONLOCKED, NODE_BUTTON_ONLOCKED_START_FRAME, NODE_BUTTON_ONLOCKED_END_FRAME, LOGO_FRAME_RATE, -1);
	animator->createAnim(ONCOMPLETED, NODE_BUTTON_ONCOMPLETED_START_FRAME, NODE_BUTTON_ONCOMPLETED_END_FRAME, LOGO_FRAME_RATE, -1);
	animator->play(ONOUT);
}

void MapScene::handleInput() {
	GameState::handleInput();

	// Opciones
	if (gmCtrl_.pause()) {
		SDLApplication::pushNewScene<OptionsMenuScene>();
	}
	// Atrás
	else if (gmCtrl_.goBack()) {
		exitButton->setAsCurrentButton();
	}

	// Scroll
	camTr->setY(camTr->getY() - gmCtrl_.scroll(false));
	if (camTr->getY() > camYLimit) camTr->setY(camYLimit);
	else if (camTr->getY() < 0) camTr->setY(0);
}

// Mueve la camara a la altura de los siguientes al nodo actual
void MapScene::moveCamera() {
	Transform* tr = camera->getComponent<Transform>();
	float prevY = tr->getY();
	tr->setY(prevY + NODE_POSITION_Y);
}

void MapScene::resetSelectedButton() {
	inventoryButton->setAsCurrentButton();
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
						Vector2D pos = Vector2D(0, (int)WIN_HEIGHT - NODE_POSITION_Y * (alt + 3) + NODE_HEIGHT);
						
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
