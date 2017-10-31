#include <iostream>
#include <SDL2/SDL.h>

#include "window.h"

// Time related globals
int const FPS = 60;
int const DELAY_TIME = 1000.0f/FPS;

int main(int argc, char** argv) {
	Window* mainWindow = NULL;
	Uint32 frameStart, frameTime;

    // Init the window
	mainWindow = new Window(600, 480);

    // Main loop
	while(mainWindow->isRunning()) {
		frameStart = SDL_GetTicks();

		mainWindow->handleEvents();
		mainWindow->update();
		mainWindow->render();

		frameTime = SDL_GetTicks() - frameStart;
		if(frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	return 0;
}

