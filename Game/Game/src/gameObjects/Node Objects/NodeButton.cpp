#include "NodeButton.h"
#include "../../core/SDLApplication.h"

void NodeButton::initGameObject(Node* nodeIt, CallBack _cb, Vector2D pos) {

	addComponent<Transform>(pos, Vector2D(), Constant::getFloat("NODE_WIDTH"), Constant::getInt("NODE_HEIGHT"));
	Animator* animator = addComponent<Animator>(SDLApplication::getTexture(nodeIt->getTextureKey()), NODE_FRAME_WIDTH, NODE_FRAME_HEIGHT, NODE_FRAME_ROWS, NODE_FRAME_COLUMNS);
	addComponent<NodeButtonComponent>(_cb, nodeIt->getState());

	animator->createAnim(Constant::getString("ONOUT"), Constant::getInt("NODE_BUTTON_ONOUT_START_FRAME"), Constant::getInt("NODE_BUTTON_ONOUT_END_FRAME"), Constant::getInt("ONCLICK_ONOUT_SPEED"), -1);
	animator->createAnim(Constant::getString("ONOVER"), Constant::getInt("NODE_BUTTON_ONOVER_START_FRAME"), Constant::getInt("NODE_BUTTON_ONOVER_END_FRAME"), Constant::getInt("ONOVER_SPEED"), 1);
	animator->createAnim(Constant::getString("ONCLICK"), Constant::getInt("NODE_BUTTON_ONCLICK_START_FRAME"), Constant::getInt("NODE_BUTTON_ONCLICK_END_FRAME"), Constant::getInt("ONCLICK_ONOUT_SPEED"), -1);
	animator->createAnim(Constant::getString("ONLOCKED"), Constant::getInt("NODE_BUTTON_ONLOCKED_START_FRAME"), Constant::getInt("NODE_BUTTON_ONLOCKED_END_FRAME"), Constant::getInt("LOGO_FRAME_RATE"), -1);
	animator->createAnim(Constant::getString("ONCOMPLETED"), Constant::getInt("NODE_BUTTON_ONCOMPLETED_START_FRAME"), Constant::getInt("NODE_BUTTON_ONCOMPLETED_END_FRAME"), Constant::getInt("LOGO_FRAME_RATE"), -1);
	animator->play(Constant::getString("ONOUT"));
}