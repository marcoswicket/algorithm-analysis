#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <vector>
#include "appstate.h"
#include "window.h"
#include "menubutton.h"
#include "convexhullstate.h"

class MenuButton;

// First screen state
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

	std::vector<MenuButton*> menuButtons;

	static void menuToPlay();
	static void exitFromMenu();

	static const std::string menuID;

	Uint8 bgColor[4];
};

#endif // MAINMENUSTATE_H
