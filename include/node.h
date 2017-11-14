#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2d.h"
#include "window.h"
#include "types.h"

enum NodeColor {
	Red,
	Blue,
	Purple
};

// Generic node structure for the algorithms presented
// in class;
class Node {
public:
	Node(Vector2D* position_, int width_, int height_);
	~Node();
	
	void update();
	void render();

	void changeColor(NodeColor nodeColor);

	float getX(){ return position->getX() + (width/2); }
	float getY(){ return position->getY() + (height/2); }

	int getWidth() { return width; }
	int getHeight() { return height; }

    bool collision(int x, int y);
private:
	Vector2D* position;
	int width, height;

	SDL_Rect rect;
	Color color;
};

#endif // NODE_H
