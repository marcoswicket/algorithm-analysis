#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

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
	// Jarvis algorithm methods and variables
	void JarvisAlgorithm();
	int l, // leftmost point
		p, // point we are doing the operation
		q; // point we are searching counterclockwise
	int jarvisFlag; 	// Flag for jarvis state
	int step;	// Step we are in the algorithm
	std::vector<Node*> hull;
	
	
	// Utility
	int orientation(Node* p, Node* q, Node* r);

	std::vector<Node*> nodes;
	Color bgColor;

	// Are we doing operations?
	bool executingAlgorithm;
	bool algorithmDone;

	// Mouse flags
    int stateLeft, stateRight;
	
	static const std::string convexID;
};

#endif // CONVEXHULL_H
