#ifndef APPSTATEMACHINE_H
#define APPSTATEMACHINE_H

#include <vector>
#include "appstate.h"

// Class for managing the App states
class AppStateMachine {
public:
	AppStateMachine(){}
	~AppStateMachine(){}

	void update();
	void render();

	void pushState(AppState* appState);
	void changeState(AppState* appState);
	void popState();

	void clean();

	std::vector<AppState*>& getAppState() { return appStates; }
private:
	std::vector<AppState*> appStates;
};

#endif // APPSTATEMACHINE_H
