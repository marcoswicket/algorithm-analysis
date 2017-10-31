#include "convexhullstate.h"

const std::string ConvexHullState::convexID = "CONVEX";

void ConvexHullState::update() {
    // Create a point by clicking in the screen with the left mouse button
    if(InputHandler::Instance()->getMouseButtonState(LEFT) && state == RELEASE) {
        int x = InputHandler::Instance()->getMousePosition()->getX();
        int y = InputHandler::Instance()->getMousePosition()->getY();
        nodes.push_back(new Node(new Vector2D(x, y), 10, 10));
        state = CLICKED;
    } else if(!InputHandler::Instance()->getMouseButtonState(LEFT)) {
        state = RELEASE;
    }

    // Delete a point by clicking on top of it with right mouse button
    if(InputHandler::Instance()->getMouseButtonState(RIGHT)) {
        for(int i = 0 ; i < (int) nodes.size() ; i++) {
           int x = InputHandler::Instance()->getMousePosition()->getX();
           int y = InputHandler::Instance()->getMousePosition()->getY();
           if(nodes[i]->collision(x, y)) {
                delete nodes[i];
                nodes.erase(nodes.begin()+i);
           }
        }
    }
}

void ConvexHullState::render() {
    for(int i = 0 ; i < (int) nodes.size() ; i++) {
        nodes[i]->render();
    }
	SDL_SetRenderDrawColor(Window::getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

bool ConvexHullState::onEnter() {
	bgColor.r = 234;
	bgColor.g = 255;
	bgColor.b = 208;
	bgColor.a = 255;

    state = RELEASE;

    return true;
}

bool ConvexHullState::onExit() {
	return true;
}


