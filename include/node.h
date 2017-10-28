#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>

#include "vector2d.h"
#include "window.h"
#include "types.h"

class Node {
public:
	Node();
	~Node();
	
	void update();
	void render();

private:
	Vector2D* position;
	int width, height;

	SDL_Rect rect;
	Color color;
};

#endif // NODE_H
