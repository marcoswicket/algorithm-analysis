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
            std::cout << "Executing Jarvis Algorithm" << std::endl;
            step = 0;
            executingAlgorithm = true;
            JarvisAlgorithm();
        }
    } else {
        JarvisAlgorithm();
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
    if(executingAlgorithm)	SDL_Delay(750);

    for(i = 0 ; i < (int) nodes.size() ; i++) {
        nodes[i]->render();
    }
    if(hull.size() > 1) {
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

bool ConvexHullState::onEnter() {
    bgColor.r = 234;
    bgColor.g = 255;
    bgColor.b = 208;
    bgColor.a = 255;

    stateLeft = RELEASE;
    stateRight = RELEASE;

    executingAlgorithm = false;
    algorithmDone = false;

    return true;
}

bool ConvexHullState::onExit() {
    // TODO: Free, cleanup and state change
    return true;
}

// Define the orientation of the point
int ConvexHullState::orientation(Node* p, Node* q, Node* r) {
    int val = (q->getY() - p->getY()) * (r->getX() - q->getX()) 
            - (q->getX() - p->getX()) * (r->getY() - q->getY());

    if(val == 0) return 0; 	// colinear
    return (val > 0) ? 1 : 2; // clock or counterclock
}

void ConvexHullState::JarvisAlgorithm() {
    if(nodes.size() < 3) {
        // Jarvis
        executingAlgorithm = false;
        return;	
    }

    //SDL_Delay(50);

    if(step == 0)  {
        // Find the leftmost point
        for(int i = 1; i < (int) nodes.size() ; i++) {
            if(nodes[i]->getX() < nodes[l]->getX()) {
                l = i;
            }
        }
        nodes[l]->changeColor(Red); // Show who the leftmost is;
        p = l;
        step++;
        std::cout << "Step: " << step << std::endl; 
        return;
    } else if(step == 1) {
        std::cout << "Jarvis Step 1" << std::endl;

        // Add current point to the hull
        // Selected point changes color
        hull.push_back(nodes[p]);
        nodes[p]->changeColor(Red); 

        q = (p + 1) % nodes.size();
        for(int i = 0; i < (int) nodes.size(); i++) {
            if(orientation(nodes[p], nodes[i], nodes[q]) == 2) {
                q = i;
            }
        }
        p = q;

        if(p == l) {
            step++;
        }		
    } else if(step == 2) {
        std::cout << "Jarvis Step 2" << std::endl;
        executingAlgorithm = false;
        algorithmDone = true;
    }
}

