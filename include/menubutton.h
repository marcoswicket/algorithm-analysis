#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SDL2/SDL.h>
#include <iostream>

#include "vector2d.h"
#include "window.h"

enum button_state { 
	MOUSE_OFF = 1,
	MOUSE_ON = 2,
	CLICKED = 3
};

typedef struct ButtonColor {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} ButtonColor;

class MenuButton {
public:
	MenuButton(void (*callback_)(), int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void setPosition(int x, int y) { position->setPosition(x, y); }

	void update();
	void render();
private:
	Vector2D* position;
	int width, height;
	int state;

	void (*callback)();

	ButtonColor color;

	SDL_Rect rect;
};

#endif // MENUBUTTON_H
