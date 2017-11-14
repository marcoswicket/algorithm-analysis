#include "inputhandler.h"
#include "window.h"

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler() : mousePosition(new Vector2D(0,0)), keyState(0){
	for(int i = 0 ; i < 3 ; i++) {
		mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler() {
	delete mousePosition;
	mouseButtonStates.clear();
}

void InputHandler::clean(){}

void InputHandler::reset() {
	mouseButtonStates[LEFT] = false;
	mouseButtonStates[RIGHT] = false;
	mouseButtonStates[MIDDLE] = false;
}

void InputHandler::update() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			Window::quitApplication();
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}
	}
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
	if(keyState != 0) {
		if(keyState[key] == 1) return true;
		else return false;
	}
}

bool InputHandler::getMouseButtonState(int buttomNumber) const {
	return mouseButtonStates[buttomNumber];
}

Vector2D* InputHandler::getMousePosition() const {
	return mousePosition;
}

void InputHandler::onMouseMove(SDL_Event &event) {
	mousePosition->setX(event.motion.x);
	mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event) {
	if(event.button.button == SDL_BUTTON_LEFT) {
		mouseButtonStates[LEFT] = true;
	}

	if(event.button.button == SDL_BUTTON_MIDDLE) {
		mouseButtonStates[MIDDLE] = true;
	}

	if(event.button.button == SDL_BUTTON_RIGHT) {
		mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event) {
	if(event.button.button == SDL_BUTTON_LEFT) {
		mouseButtonStates[LEFT] = false;
	}

	if(event.button.button == SDL_BUTTON_MIDDLE) {
		mouseButtonStates[MIDDLE] = false;
	}

	if(event.button.button == SDL_BUTTON_RIGHT) {
		mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onKeyUp() {
	keyState = SDL_GetKeyboardState(0);		
}

void InputHandler::onKeyDown() {
	keyState = SDL_GetKeyboardState(0);
}
