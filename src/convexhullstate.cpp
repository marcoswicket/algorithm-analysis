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

	return true;
}

bool ConvexHullState::onExit() {
	// TODO: Free, cleanup and state change
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

// Square root distance, without sqrt. Why? Nothing to gain, and lose performance
int ConvexHullState::distance(Node* p, Node* q) {
	return (p->getX() - q->getX()) * (p->getX() - q->getX())
		+ (p->getY() - q->getY()) * (p->getY() - q->getY());
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
		executingAlgorithm = false;
		return;	
	}

	if(step == 0)  {
		// Find the leftmost point
		for(int i = 1; i < (int) nodes.size() ; i++) 
			if(nodes[i]->getX() < nodes[l]->getX()) 
				l = i;

		nodes[l]->changeColor(Red); // Show who the leftmost is;
		p = l;
		step++;
		//std::cout << "Step: " << step << std::endl; 
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
		// Swap members around
		std::iter_swap(nodes.begin(), nodes.begin() + leastY);

		// Sort the points based on their polar angle
		std::sort(nodes.begin() + 1, nodes.end(), *this);

		hull.push_back(nodes[0]);
		hull.push_back(nodes[1]);
		hull.push_back(nodes[2]);
		paintNodes();
		step++;
	} else if(step == 2) {
		for(int i = 3 ; i < nodes.size() ; i++) {
			Node* top = hull.back();
			hull.pop_back();

			nodes[i]->changeColor(Red);

			while(orientation(hull.back(), top, nodes[i]) != 1) {
				top = hull.back();
				hull.pop_back();
			}

			hull.push_back(top);
			hull.push_back(nodes[i]);
			paintNodes();
		}
		step++;
	} else {
		executingAlgorithm = false;
		algorithmDone = true;
	}
}
