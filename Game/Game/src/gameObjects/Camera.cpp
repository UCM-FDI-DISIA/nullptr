#include "Camera.h"

// Constructora por defecto
Camera::Camera() : pos(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2)) {
	transform = addComponent<Transform>(pos);
}

const Vector2D& Camera::getPosition() { 
	return pos; 
}

//Camera::Camera(GameObject* _followObject) {
//	centerX = WIN_WIDTH / 2;
//	centerY = WIN_HEIGHT / 2;
//	transform = addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, 0);
//	cameraComponent = addComponent<CameraComponent>();
//	followObject = _followObject;
//	followObjectTransform = getComponent<Transform>();
//}
//Camera::Camera() : followObject(nullptr), followObjectTransform(nullptr), posX(0), posY(0), width(WIN_WIDTH), height(WIN_HEIGHT), rotation(0) {
//	transform = addComponent<Transform>(Vector2D(posX, posY), Vector2D(0, 0), width, height);
//	cameraComponent = addComponent<CameraComponent>();
//}
//
//Camera::Camera(GameObject* _followObject) : followObject(_followObject), posX(0), posY(0), width(WIN_WIDTH), height(WIN_HEIGHT), rotation(0) {
//	transform = addComponent<Transform>(Vector2D(posX, posY), Vector2D(0,0), width, height);
//	cameraComponent = addComponent<CameraComponent>();
//	followObjectTransform = getComponent<Transform>();
//}
//
//// Con SDL_Rect
//Camera::Camera(GameObject* _followObject, SDL_Rect _rect, float _rotation) : followObject(_followObject), posX(_rect.x), posY(_rect.y), width(_rect.w), height(_rect.h), rotation(_rotation) {
//	transform = addComponent<Transform>(Vector2D(posX, posY), Vector2D(0, 0), width, height, rotation);
//	cameraComponent = addComponent<CameraComponent>();
//	followObjectTransform = getComponent<Transform>();
//}
//
//// Con más parámetros
//Camera::Camera(GameObject* _followObject, float _posX, float _posY, float _width, float _height, float _rotation) : followObject(_followObject), posX(_posX), posY(_posY), width(_width), height(_height), rotation(_rotation) {
//	transform = addComponent<Transform>(Vector2D(posX, posY), Vector2D(0, 0), width, height, rotation);
//	cameraComponent = addComponent<CameraComponent>();
//	followObjectTransform = getComponent<Transform>();
//}