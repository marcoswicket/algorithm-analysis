#include <iostream>
#include <assert.h>

#include "mainmenustate.h"

const std::string MainMenuState::menuID = "MENU";

// Button callbacks
void MainMenuState::menuToPlay() {
	// TODO: Need to properly create a new state;
	//Window::getAppStateMachine()->changeState();
	std::cout << "I'm working bro relax" << std::endl;
}

void MainMenuState::exitFromMenu() {
	Window::quitApplication();
}

void MainMenuState::update() {
	// TODO: Properly make colision with the buttons
	for(int i = 0 ; i < menuButtons.size() ; i++) {
		menuButtons[i]->update();
	}
}

void MainMenuState::render() {
	// TODO: Render all objects related to this thing
	for(int i = 0 ; i < menuButtons.size() ; i++) {
		menuButtons[i]->render();
	}
	SDL_SetRenderDrawColor(Window::getRenderer(), bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
}

bool MainMenuState::onEnter() {
	// TODO: Alloc all things
	bgColor[0] = 149;
	bgColor[1] = 225;
	bgColor[2] = 211;
	bgColor[3] = 255;

	// Thats a long line, just adding the buttons to our button vector
	menuButtons.push_back(new MenuButton(&menuToPlay, Window::getWindowWidth() * 0.105, Window::getWindowHeight() * 0.87 - 50, 243, 129, 129, 255));
	menuButtons.push_back(new MenuButton(&exitFromMenu, Window::getWindowWidth() * 0.58, Window::getWindowHeight() * 0.87 - 50, 243, 129, 129, 255));
	return true;
}

bool MainMenuState::onExit() {
	// TODO: Free all things
	return true;
}

//void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
	// TODO: Set callbacks for buttons
//}
