#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>

#include "appstate.h"
#include "window.h"
#include "node.h"
#include "inputhandler.h"

enum state {
    CLICK = 1,
    RELEASE = 2
};

enum algorithm {
	JARVIS = 1,
	GRAHAM = 2
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
	bool operator()(Node* p, Node* q);
private:
	// Jarvis algorithm methods and variables
	void JarvisAlgorithm();
	int l, // leftmost point
		p, // point we are doing the operation
		q; // point we are searching counterclockwise
	int jarvisFlag; 	// Flag for jarvis state
	int step;	// Step we are in the algorithm
	
	// GrahamScan methods and variables
	void GrahamScan();
	int distance(Node* p, Node* q);
	int leastY; 	// Least y

	// Utility
	int orientation(Node* p, Node* q, Node* r);
	void paintNodes(); // Set nodes color based on state
	void reset(); // Reset the screen
	void cleanNotSelected(); // Return the not selected nodes to their color
	void clean_nodes();
	void clean_hull(); 
	void sort(); // Sort nodes by their polar angle
	int j;

	// Which algorithm are we executing
	int algorithm;

	// Nodes and Hull data structures
	std::vector<Node*> nodes;
	std::vector<Node*> hull;

	// Background color
	Color bgColor;

	// Are we doing operations?
	bool executingAlgorithm;
	bool algorithmDone;

	// Mouse flags
    int stateLeft, stateRight;
	
	static const std::string convexID;
};

#endif // CONVEXHULL_H
