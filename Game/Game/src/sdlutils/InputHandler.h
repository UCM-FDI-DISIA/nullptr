// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>

#include "../utils/Singleton.h"
#include "../core/Vector2D.h"

#define CONTROLLER_AXIS_MAX 32767.0f
#define CONTROLLER_AXIS_MIN -32768.0f
#define CONTROLLER_AXIS_POS_DEADZONE (CONTROLLER_AXIS_MAX * 0.3f)
#define CONTROLLER_AXIS_NEG_DEADZONE (CONTROLLER_AXIS_MIN * 0.3f)

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

class InputHandler: public Singleton<InputHandler> {

	friend Singleton<InputHandler> ;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	virtual ~InputHandler() {
		onControllerDeviceRemoved();
	}

	// clear the state
	inline void clearState() {
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;
		isMouseButtonEvent_ = false;
		isMouseMotionEvent_ = false;
		isMouseWheelEvent_ = false;
		mouseWheelUp_ = false;
		mouseWheelDown_ = false;
		for (auto i = 0u; i < 3; i++) {
			mbState_[i] = false;
		}
		isControllerButtonDownEvent_ = false;
		isControllerButtonUpEvent_ = false;
		isControllerAxisMotionEvent_ = false;
	}

	// update the state with a new event
	inline void update(const SDL_Event &event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		case SDL_MOUSEWHEEL:
			onMouseWheelEvent(event);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			onControllerDeviceAdded();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			onControllerDeviceRemoved();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			onControllerButtonDown(event);
			break;
		case SDL_CONTROLLERBUTTONUP:
			onControllerButtonUp(event);
			break;
		case SDL_CONTROLLERAXISMOTION:
			onControllerAxisMotion(event);
			break;
		case SDL_WINDOWEVENT:
			handleWindowEvent(event);
			break;
		default:
			break;
		}
	}

	// refresh
	inline void refresh() {
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}

	// close window event
	inline bool closeWindowEvent() {
		return isCloseWindoEvent_;
	}

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}

	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyJustDown(SDL_Scancode key) {
		return keyDownEvent() && kbState_[key] == 1;
	}

	inline bool isKeyJustDown(SDL_Keycode key) {
		return isKeyJustDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyJustUp(SDL_Scancode key) {
		return keyUpEvent() && kbState_[key] == 0;
	}

	inline bool isKeyJustUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}

	inline bool isMouseWheelEvent() {
		return isMouseWheelEvent_;
	}

	inline bool mouseWheelUp() {
		return isMouseWheelEvent() && mouseWheelUp_;
	}

	inline bool mouseWheelDown() {
		return isMouseWheelEvent() && mouseWheelDown_;
	}


	inline const Vector2D& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	// TODO add support for Joystick, see Chapter 4 of
	// the book 'SDL Game Development'


	inline bool controllerButtonDownEvent() {
		return isControllerButtonDownEvent_;
	}

	inline bool controllerButtonUpEvent() {
		return isControllerButtonUpEvent_;
	}

	inline bool controllerAxisMotionEvent() {
		return isControllerAxisMotionEvent_;
	}

	inline bool isControllerButtonDown(SDL_GameControllerButton b) {
		return controllerButtonDownEvent() && SDL_GameControllerGetButton(controller_, b) == 1;
	}

	inline bool isControllerButtonUp(SDL_GameControllerButton b) {
		return controllerButtonUpEvent() && SDL_GameControllerGetButton(controller_, b) == 0;
	}

	inline int getControllerAxis(SDL_GameControllerAxis b) {
		int axis = SDL_GameControllerGetAxis(controller_, b);
		float dz = (axis >= 0) ? CONTROLLER_AXIS_POS_DEADZONE : CONTROLLER_AXIS_NEG_DEADZONE;
		float max = (axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN;
		
		if (abs(axis) < abs(dz)) return 0;
		return axis - (dz * ((max - axis) / (max - dz)));
	}

	inline float getNormalizedControllerAxis(SDL_GameControllerAxis b) {
		float axis = getControllerAxis(b);
		return axis / abs((axis >= 0) ? CONTROLLER_AXIS_MAX : CONTROLLER_AXIS_MIN);
	}

private:
	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0); 
		controller_ = nullptr;
		clearState();
	}

	inline void onKeyDown(const SDL_Event&) {
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(const SDL_Event &event) {
		isMouseMotionEvent_ = true;
		mousePos_.setX(event.motion.x);
		mousePos_.setY(event.motion.y);
	}

	inline void onMouseButtonChange(const SDL_Event &event, bool isDown) {
		isMouseButtonEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = isDown;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = isDown;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = isDown;
			break;
		default:
			break;
		}
	}

	inline void onMouseWheelEvent(const SDL_Event& event) {
		isMouseWheelEvent_ = true;
		if (event.wheel.y < 0) mouseWheelDown_ = true;
		if (event.wheel.y > 0) mouseWheelUp_ = true;
	}

	inline void handleWindowEvent(const SDL_Event &event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			isCloseWindoEvent_ = true;
			break;
		default:
			break;
		}
	}

	inline void onControllerDeviceAdded() {
		if (controller_ == nullptr) {
			controller_ = SDL_GameControllerOpen(0);
#ifdef _DEBUG
			std::cout << "GameController connected." << std::endl;
#endif
		}
	}
	inline void onControllerDeviceRemoved() {
		if (controller_ != nullptr) {
			SDL_GameControllerClose(controller_);
			controller_ = nullptr;
#ifdef _DEBUG
			std::cout << "GameController disconnected." << std::endl;
#endif
		}
	}

	inline void onControllerButtonDown(const SDL_Event& event) {
		isControllerButtonDownEvent_ = true;

	}
	inline void onControllerButtonUp(const SDL_Event& event) {
		isControllerButtonUpEvent_ = true;

	}
	inline void onControllerAxisMotion(const SDL_Event& event) {
		isControllerAxisMotionEvent_ = true;

	}

	bool isCloseWindoEvent_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	bool isMouseWheelEvent_;
	bool mouseWheelUp_;
	bool mouseWheelDown_;
	bool isControllerButtonDownEvent_;
	bool isControllerButtonUpEvent_;
	bool isControllerAxisMotionEvent_;
	Vector2D mousePos_;
	std::array<bool, 3> mbState_;
	const Uint8 *kbState_;
	SDL_GameController* controller_;
}
;

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}
