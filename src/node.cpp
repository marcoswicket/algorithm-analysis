#include "node.h" 

Node::Node(Vector2D* position_, int width_, int height_) : 
    position(position_), width(width_), height(height_) {

    changeColor(Purple);
	rect.w = width;
    rect.h = height;
    rect.x = position->getX();
    rect.y = position->getY();
}

Node::~Node() {
    delete(position);
}

bool Node::collision(int x, int y) {
    if(position->getX() <= x && position->getX() + width >= x 
        && position->getY() <= y && position->getY() + height >= y) {
        return true;
    }

    return false;
}

void Node::update() {
}

void Node::render() {
    SDL_SetRenderDrawColor(Window::getRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Window::getRenderer(), &rect);	
}

void Node::changeColor(NodeColor nodeColor) {
	if(nodeColor == Purple) {
		color.r = 75;
		color.g = 0;
		color.b = 150;
		color.a = 255;
	}
	if(nodeColor == Blue) {
		color.r = 50;
		color.g = 0;
		color.b = 175;
		color.a = 255;
	}
	if(nodeColor == Red) {
		color.r = 175;
		color.g = 0;
		color.b = 0;
		color.a = 255;
	}
}
