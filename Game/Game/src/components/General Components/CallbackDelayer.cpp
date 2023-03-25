#include "CallbackDelayer.h"
#include "../../core/SDLApplication.h"

void CallbackDelayer::update()
{
	timer += SDLApplication::instance()->getDeltaTime();

	if (timer >= requestedDelay)
	{
		callback();
	}
}
