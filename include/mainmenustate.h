#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <vector>
#include "appstate.h"
#include "window.h"

class MainMenuState : public AppState {
public:
	virtual ~MainMenuState(){}

	virtual void update();
	virtual void render();
	
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return menuID; }

private:
	//virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void menuToPlay();
	static void exitFromMenu();

	static const std::string menuID;
};

#endif // MAINMENUSTATE_H
