#include "convexhullstate.h"

const std::string ConvexHullState::convexID = "CONVEX";


void ConvexHullState::update() {
	
}

void ConvexHullState::render() {
	SDL_SetRenderDrawColor(Window::getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

bool ConvexHullState::onEnter() {
	bgColor.r = 234;
	bgColor.g = 255;
	bgColor.b = 208;
	bgColor.a = 255;
}

bool ConvexHullState::onExit() {
	
}


