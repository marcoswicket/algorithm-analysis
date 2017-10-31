#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "inputhandler.h"
#include "appstatemachine.h"
#include "mainmenustate.h"

class Window {
public:
	Window(int width_, int height_);
	~Window();

	bool init();

	void render();
	void update();
	void handleEvents();
	void clean();

	void quit() { running = false; }

    // Global utilities
	static SDL_Renderer* getRenderer() { return renderer; }
	const static SDL_Window* getWindow() { return window; }
	static int getWindowWidth() { return width; }
	static int getWindowHeight(){ return height; }
	static AppStateMachine* getAppStateMachine() { return appStateMachine; }

    // State methods
	bool isRunning() const { return running; }
	static void quitApplication() { running = false; }

private:
	static int width;
	static int height;

	// Is the application running?
	static bool running;

	static SDL_Renderer* renderer;
	static SDL_Window* window;

	static AppStateMachine* appStateMachine;
};

#endif // WINDOW_H
