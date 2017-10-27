#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "inputhandler.h"

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

	SDL_Renderer* getRenderer() const { return renderer; }
	SDL_Window* getWindow() const { return window; }
	int getWindowWidth() const { return width; }
	int getWindowHeight() const { return height; }

	bool isRunning() const { return running; }
	static void quitApplication() { running = false; }

private:
	int const width;
	int const height;

	// Is the application running?
	static bool running;

	SDL_Renderer* renderer;
	SDL_Window* window;
};

#endif // WINDOW_H
