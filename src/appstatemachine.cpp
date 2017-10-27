#include <iostream>

#include "appstatemachine.h"

void AppStateMachine::clean() {
	if(!appStates.empty()) {
		appStates.back()->onExit();
		delete appStates.back();
		appStates.clear();
	}
}

void AppStateMachine::update() {
	if(!appStates.empty()) {
		appStates.back()->update();
	}
}

void AppStateMachine::render() {
	if(!appStates.empty()) {
		appStates.back()->render();
	}
}

void AppStateMachine::pushState(AppState* appState) {
	appStates.push_back(appState);
	appStates.back()->onEnter();
}

void AppStateMachine::popState() {
	if(!appStates.empty()) {
		appStates.back()->onExit();
		appStates.pop_back();
	}
	appStates.back()->resume();
}

void  AppStateMachine::changeState(AppState *appState) {
	if(!appStates.empty()){
		if(appStates.back()->getStateID() == appState->getStateID()) {
			return; // do nothing
		}

		appStates.back()->onExit();
		appStates.pop_back();
	}

	// initialise it
	appState->onEnter();

	// push back our new state
	appStates.push_back(appState);
}
