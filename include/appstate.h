#ifndef APPSTATE_H
#define APPSTATE_H

#include <string>
#include <vector>

// Virtual class for App States
class AppState {
public:
	virtual ~AppState(){}

	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void resume() {}

	virtual std::string getStateID() const = 0;

protected:
	AppState() : loadingComplete(false), exiting(false) {}

	bool loadingComplete;
	bool exiting;

	std::vector<std::string> textureIDList;
};

#endif // APPSTATE_H
