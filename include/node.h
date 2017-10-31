#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2d.h"
#include "window.h"
#include "types.h"

// Generic node structure for the algorithms presented
// in class;
class Node {
public:
	Node(Vector2D* position_, int width_, int height_);
	~Node();
	
	void update();
	void render();

    bool collision(int x, int y);
private:
	Vector2D* position;
	int width, height;

	SDL_Rect rect;
	Color color;
};

#endif // NODE_H
