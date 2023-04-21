#include "Camera.h"
#include "../../core/SDLApplication.h"

/*
	En cada escena se crea una camara inicializada en la posicion (0,0),
	de forma que si no tiene un followObject, cuando se añade un GameObject
	a la escena con un transform y un image, no se modifica su metodo render
	al estar sumando (0,0).
	El CameraComponent es el que gestiona el renderizado de los objetos que
	tengan atachado la camara en su componente Image
*/

// Constructora
Camera::Camera() : followObject(nullptr) {
	transform = addComponent<Transform>(Vector2D(), Vector2D(), Constant::getInt("WIN_WIDTH"), Constant::getInt("WIN_HEIGHT"));
	cameraComponent = addComponent<CameraComponent>();
}

// Destructora
Camera::~Camera() {
	// El delete del objeto seguido se debe hacer en la destructora de la propia clase
	followObject = nullptr;
}

// Asigna el objeto a seguir
void Camera::startFollowObject(GameObject* followObject_) {
	followObject = followObject_;
	cameraComponent->setFollowObject(followObject);
}

// Devuelve el followObject
GameObject* Camera::getFollowObject() { 
	return followObject; 
}

// Devuelve la posicion de la camara
Vector2D Camera::getOffset() const{
	return transform->getPos();
}