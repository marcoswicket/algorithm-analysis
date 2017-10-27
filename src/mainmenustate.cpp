#include <iostream>
#include <assert.h>

#include "window.h"
#include "mainmenustate.h"

const std::string MainMenuState::menuID = "MENU";

// Button callbacks
void MainMenuState::menuToPlay() {
	// TODO: Need to properly create a new state;
	//Window::getAppStateMachine()->changeState();
}

void MainMenuState::exitFromMenu() {
	Window::quitApplication();
}

void MainMenuState::update() {
	// TODO: Properly make colision with the buttons
}

void MainMenuState::render() {
	// TODO: Render all objects related to this thing
	SDL_SetRenderDrawColor(Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
}

bool MainMenuState::onEnter() {
	// TODO: Alloc all things
	return true;
}

bool MainMenuState::onExit() {
	// TODO: Free all things
	return true;
}

//void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
	// TODO: Set callbacks for buttons
//}
