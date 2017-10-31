#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <vector>

#include "appstate.h"
#include "window.h"
#include "node.h"
#include "inputhandler.h"

enum state {
    CLICK = 1,
    RELEASE = 2
};

// In theory the main state that will contain the convex hull algorithm
class Node;
class ConvexHullState : public AppState {
public:
	virtual ~ConvexHullState(){}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return convexID; }
private:
	std::vector<Node*> nodes;

	static const std::string convexID;

	Color bgColor;

    int state;
};

#endif // CONVEXHULL_H
