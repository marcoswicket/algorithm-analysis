#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SDL2/SDL.h>
#include <iostream>

#include "vector2d.h"
#include "window.h"
#include "types.h"

enum button_state { 
	MOUSE_OFF = 1,
	MOUSE_ON = 2,
	CLICKED = 3
};

class MenuButton {
public:
	MenuButton(void (*callback_)(), int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setPosition(int x, int y) { position->setPosition(x, y); }

	void update();
	void render();
	void clean();
private:
	Vector2D* position;
	int width, height;
	int state;

	void (*callback)();

	Color color;

	SDL_Rect rect;
};

#endif // MENUBUTTON_H
