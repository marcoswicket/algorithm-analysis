#include "convexhullstate.h"

const std::string ConvexHullState::convexID = "CONVEX";

void ConvexHullState::update() {
	if(!executingAlgorithm)	{
		// Create a point by clicking in the screen with the left mouse button
		if(InputHandler::Instance()->getMouseButtonState(LEFT) && stateLeft == RELEASE) {
			int x = InputHandler::Instance()->getMousePosition()->getX();
			int y = InputHandler::Instance()->getMousePosition()->getY();
			nodes.push_back(new Node(new Vector2D(x, y), 10, 10));
			stateLeft = CLICKED;
		} else if(!InputHandler::Instance()->getMouseButtonState(LEFT)) {
			stateLeft = RELEASE;
		}

		// Delete a point by clicking on top of it with right mouse button
		if(InputHandler::Instance()->getMouseButtonState(RIGHT) && stateRight == RELEASE) {
			for(int i = 0 ; i < (int) nodes.size() ; i++) {
				int x = InputHandler::Instance()->getMousePosition()->getX();
				int y = InputHandler::Instance()->getMousePosition()->getY();
				if(nodes[i]->collision(x, y)) {
					delete nodes[i];
					nodes.erase(nodes.begin()+i);
					stateRight = CLICKED;
				}
			}
		} else if (!InputHandler::Instance()->getMouseButtonState(RIGHT)) {
			stateRight = RELEASE;
		}

		if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Q)) {
			//std::cout << "Executing Jarvis Algorithm" << std::endl;
			step = 0;
			clean_hull();
			executingAlgorithm = true;
			algorithmDone = false;
			algorithm = JARVIS;
			JarvisAlgorithm();
		} else if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
			//std::cout << "Executing Graham Algorithm" << std::endl;
			step = 0;
			clean_hull();
			executingAlgorithm = true;
			algorithmDone = false;
			algorithm = GRAHAM;
			GrahamScan();
		} else if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_E)) {
			step = 0;
			clean_hull();
			executingAlgorithm = true;
			algorithmDone = false;
			algorithm = QUICKHULL;
			QuickHull();
		}

		if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_R)) {
			//std::cout << "Resetting" << std::endl;
			step = 0;
			reset();
		}
	} else {
		switch(algorithm){
		case JARVIS:
			JarvisAlgorithm();
			break;
		case GRAHAM:
			GrahamScan();
			break;
		case QUICKHULL:
			QuickHull();
			break;
		default:
			std::cout << "Unknown option: " << algorithm << std::endl;
			exit(1);
		}
	}

	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
		//if(nodes.size() > 0) {
		//nodes[0]->changeColor(Red);
		//}
		Window::quitApplication();
	}

	menuButtons[0]->update();
}

void ConvexHullState::render() {
	int i;
	// Delay for vision purposes
	if(executingAlgorithm)	SDL_Delay(50);

	for(i = 0 ; i < (int) nodes.size() ; i++) {
		nodes[i]->render();
	}
	if(hull.size() > 1) {	
		// If done lines are green else they are blue
		if(algorithmDone) SDL_SetRenderDrawColor(Window::getRenderer(), 0, 175, 0, 255);
		else SDL_SetRenderDrawColor(Window::getRenderer(), 0, 0, 175, 255);

		for(i = 0 ; i < (int) hull.size() - 1 ; i++) {
			SDL_RenderDrawLine(Window::getRenderer(), 
					hull[i]->getX(), hull[i]->getY(),
					hull[i+1]->getX(), hull[i+1]->getY());
		}
		SDL_RenderDrawLine(Window::getRenderer(), 
				hull[0]->getX(), hull[0]->getY(),
				hull[i]->getX(), hull[i]->getY());
	}
	for(int i = 0 ; i < menuButtons.size() ; i++) {
		menuButtons[i]->render();
		//std::cout << "Rendering button" << std::endl;
	}
	SDL_SetRenderDrawColor(Window::getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

// Change the not selected points to their default color
void ConvexHullState::cleanNotSelected() {
	for(int i = 0 ; i < (int) nodes.size() ; i++) {
		if(std::find(hull.begin(), hull.end(), nodes[i]) == hull.end())
			nodes[i]->changeColor(Purple);
	}
}

// On state enter we do all variables init
bool ConvexHullState::onEnter() {
	bgColor.r = 234;
	bgColor.g = 255;
	bgColor.b = 208;
	bgColor.a = 255;

	stateLeft = RELEASE;
	stateRight = RELEASE;

	executingAlgorithm = false;
	algorithmDone = false;

	algorithm = 0;
	j = 0;

	menuButtons.push_back(new MenuButton(NULL, Window::getWindowWidth() - Window::getWindowWidth()/4, 0, 243, 129, 129, 175, Window::getWindowWidth()/4, Window::getWindowHeight()/4));
	menuButtons[0]->loadTexture("assets/instructions.png");
	menuButtons[0]->setTextureAlpha(175);

	return true;
}

bool ConvexHullState::onExit() {
	// TODO: Free, cleanup and state change
	clean_hull();
	clean_nodes();
	for(int i = 0 ; i < menuButtons.size() ; i++) {
		menuButtons.back()->clean();
		menuButtons.pop_back();
	}
	menuButtons.clear();
	
	return true;
}


// Clean the points in the screen
void ConvexHullState::reset() {
	clean_nodes();	
	clean_hull();
}

// Clean nodes vector
void ConvexHullState::clean_nodes() {
	for(int i = 0 ; i < (int) nodes.size() ; i++) {
		nodes.back()->clean();
		nodes.pop_back();
	}
	nodes.clear();
	
}

// Clean the hull vector
void ConvexHullState::clean_hull() {
	for(int i = 0 ; i < (int) hull.size() ; i++) {
		//hull.back()->clean();
		hull.pop_back();
	}
	hull.clear();
}

// Define the orientation of the point
int ConvexHullState::orientation(Node* p, Node* q, Node* r) {
	int val = (q->getY() - p->getY()) * (r->getX() - q->getX()) 
		- (q->getX() - p->getX()) * (r->getY() - q->getY());

	if(val == 0) return 0; 	// colinear
	return (val > 0) ? 1 : 2; // clock or counterclock
}

// Find which side a point falls of from a line connected from p to q
int ConvexHullState::findSide(Node* p, Node* q, Node* r) {
	int val = (r->getY() - p->getY()) * (q->getX() - p->getX())
			- (q->getY() - p->getY()) * (r->getX() - p->getX());
	if(val == 0) return 0;
	return (val > 0) ? 1 : -1;
}

// Square root distance, without sqrt. Why? Nothing to gain, and lose performance
int ConvexHullState::distance(Node* p, Node* q) {
	return (p->getX() - q->getX()) * (p->getX() - q->getX())
		 + (p->getY() - q->getY()) * (p->getY() - q->getY());
}

// Distance from a line made by the connection of p -> q
int ConvexHullState::lineDistance(Node* p, Node* q, Node* r) {
	return abs( (r->getY() - p->getY()) * (q->getX() - p->getX())
			  - (q->getY() - p->getY()) * (r->getX() - p->getX()));
}

// Necessity for std::sort, it sorts nodes by their polar angle
bool ConvexHullState::operator()(Node* p, Node* q) {
	int order = orientation(nodes[0], p, q);
	if(order == 0) return distance(nodes[0], p) < distance(nodes[0], q);
	return (order == 1);
}

void ConvexHullState::paintNodes() {
	for(int i = 0 ; i < nodes.size() ; i++) {
		if(std::find(hull.begin(), hull.end(), nodes[i]) == hull.end()) {
			nodes[i]->changeColor(Purple);
		} else {
			nodes[i]->changeColor(Green);
		}
	}
}

void ConvexHullState::JarvisAlgorithm() {
	if(nodes.size() < 3) {
		// Jarvis
		std::cout << "Nodes size lesser than 3" << std::endl;
		executingAlgorithm = false;
		return;	
	}

	//std::cout << "Jarvis Step: " << step << std::endl;

	if(step == 0)  {
		l = 0;
		j = 0;
		// Find the leftmost point
		for(int i = 1; i < (int) nodes.size() ; i++) 
			if(nodes[i]->getX() < nodes[l]->getX()) 
				l = i;

		nodes[l]->changeColor(Red); // Show who the leftmost is;
		p = l;
		step++;
		return;
	} else if(step == 1) {
		if(j == 0) {
			//std::cout << "Jarvis Step 1" << std::endl;

			// Add current point to the hull
			// Selected point changes color
			hull.push_back(nodes[p]);
			nodes[p]->changeColor(Green);

			// Clean back not selected nodes to purple
			cleanNotSelected();
			q = (p + 1) % nodes.size();
		}  
		
		// Manual loop for clearly showing selection steps
		if(j < (int) nodes.size()) {
			if(orientation(nodes[p], nodes[j], nodes[q]) == 2) {
				// If its not on HULL and selected for candidate paints it red
				if(std::find(hull.begin(), hull.end(), nodes[j]) == hull.end()) {
					nodes[j]->changeColor(Red);
				}
				q = j;
			}
			j++;
			//std::cout << "Looping: " << j  <<std::endl;
		} else {
			j = 0;
		} 
	
		// End of the loop
		if(j == 0) {
			p = q;
			if(p == l) {
				step++;
			}		
		}
		return;
	} else if(step == 2) {
		//std::cout << "Jarvis Step 2" << std::endl;
		cleanNotSelected();
		executingAlgorithm = false;
		algorithmDone = true;
	}
}

void ConvexHullState::GrahamScan() {
	if(nodes.size() < 3) {
		executingAlgorithm = false;
		return;
	}

	if(step == 0) {
		// Get the bottom-most node
		leastY = 0;
		for(int i = 1 ; i < nodes.size() ; i++) 
			if(nodes[leastY]->getY() > nodes[i]->getY()) 
				leastY = i;
		step++;
	} else if (step == 1) {
		// Swap pivot with the first element
		std::iter_swap(nodes.begin(), nodes.begin() + leastY);

		// Sort the rest based on their polar angle in respect to the first 
		// point. A point p1 comes before p2 if the p2 has a larger polar
		// angle (in counterclockwise rotation) than p1.
		std::sort(nodes.begin() + 1, nodes.end(), *this);

		// Form a primitive hull in a stack with the 3 first points
		hull.push_back(nodes[0]);
		hull.push_back(nodes[1]);
		hull.push_back(nodes[2]);
		
		paintNodes();
		
		step++;
		j = 3;

	// Step 2 is a manual loop to search for other hull candidates
	} else if(step == 2) {
		if(j < (int) nodes.size()) {
			Node* top = hull.back();
			hull.pop_back();

			// If two or more points 
			while(orientation(hull.back(), top, nodes[j]) != 1) {
				top = hull.back();
				hull.pop_back();
			}

			hull.push_back(top);
			hull.push_back(nodes[j]);
			paintNodes();

			j++;
		} else {
			step++;
		}
	} else {
		executingAlgorithm = false;
		algorithmDone = true;
	}
}

void ConvexHullState::QuickHullExecution(Node* p1, Node* p2, int side) {
	int max_dist = 0;
	int ind = -1;

	for(int i = 0 ; i < (int)nodes.size() ; i++) {
		int temp = lineDistance(p1, p2, nodes[i]);
		if(findSide(p1, p2, nodes[i]) == side && temp > max_dist){
			ind = i;
			max_dist = temp;
		}
	}

	if(ind == -1) {
		if(std::find(hull.begin(), hull.end(), p1) == hull.end())
			hull.push_back(p1);
		if(std::find(hull.begin(), hull.end(), p2) == hull.end())
			hull.push_back(p2);
		return;
	}

	QuickHullExecution(nodes[ind], p1, -findSide(nodes[ind], p1, p2));
	QuickHullExecution(nodes[ind], p2, -findSide(nodes[ind], p2, p1));
}

void ConvexHullState::QuickHull() {
	if(nodes.size() < 3) {
		std::cout << "Not enough points" << std::endl;
		executingAlgorithm = false;
		algorithmDone = false;
		return;
	}

	if(step == 0) {
		max_x = 0;
		min_x = 0;
		for(int i = 1 ; i < (int)nodes.size() ; i++) {
			if(nodes[i]->getX() < nodes[min_x]->getX())
				min_x = i;
			if(nodes[i]->getX() > nodes[max_x]->getX())
				max_x = i;
		}

		nodes[min_x]->changeColor(Red);
		nodes[max_x]->changeColor(Red);
		step++;
	} else if(step == 1) {
		QuickHullExecution(nodes[min_x], nodes[max_x], 1);
		QuickHullExecution(nodes[min_x], nodes[max_x], -1);
		step++;
	} else {
		// Get the bottom-most node
		leastY = 0;
		for(int i = 1 ; i < hull.size() ; i++) 
			if(hull[leastY]->getY() > hull[i]->getY()) 
				leastY = i;
		// Swap pivot with the first element
		std::iter_swap(hull.begin(), hull.begin() + leastY);

		// Sort the rest based on their polar angle in respect to the first 
		// point. A point p1 comes before p2 if the p2 has a larger polar
		// angle (in counterclockwise rotation) than p1.
		std::sort(hull.begin() + 1, hull.end(), *this);

		paintNodes();

		executingAlgorithm = false;
		algorithmDone = true;
	}
}
