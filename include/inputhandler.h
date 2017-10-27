#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "vector2d.h"

enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

// Singleton
class InputHandler {
public:
	static InputHandler* Instance() {
		if(instance == 0) {
			instance = new InputHandler();
		}
		return instance;
	}

	void reset();

	void update();
	void clean();

	// Mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;

private:
	InputHandler();
	~InputHandler();

	// Mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);

	// Mouse specific variables
	std::vector<bool> mouseButtonStates;
	Vector2D* mousePosition;

	static InputHandler* instance;
};

typedef InputHandler InputHandler;

#endif // INPUTHANDLER_H
