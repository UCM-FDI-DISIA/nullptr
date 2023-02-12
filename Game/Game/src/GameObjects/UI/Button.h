#pragma once

#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"

class SDLApplication;
typedef void CallBack();
class Button : public GameObject {
private:

public:
	Button(CallBack _c, SDLApplication* game);


};