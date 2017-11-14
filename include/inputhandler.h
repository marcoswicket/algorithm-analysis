#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "vector2d.h"

// Mouse states
enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

// Singleton
class InputHandler {
public:
    // Singleton instance access
	static InputHandler* Instance() {
		if(instance == 0) {
			instance = new InputHandler();
		}
		return instance;
	}

	void reset();

    // Regular states
	void update();
	void clean();

	// Mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;

	// Keyboard events
	bool isKeyDown(SDL_Scancode key) const;

private:
	InputHandler();
	~InputHandler();

	// Mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);

	// Handle Keyboard Events
	void onKeyDown();
	void onKeyUp();

	// Mouse specific variables
	std::vector<bool> mouseButtonStates;
	Vector2D* mousePosition;

	// Keyboard state
	const Uint8* keyState;	

    // Singleton instance
	static InputHandler* instance;
};

typedef InputHandler InputHandler;

#endif // INPUTHANDLER_H
