#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
	MenuButton(void (*callback_)(), int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int width_, int height_);

	void setPosition(int x, int y) { position->setPosition(x, y); }
	void setWidth(int width_) { width = width_; }
	void setHeight(int height_) { height = height_; }
	void setTextureAlpha(int a); 

	int getWidth() { return width; }
	int getHeight() { return height; }
	Vector2D getPosition() { return *position; }

	void update();
	void render();
	void clean();

	void loadTexture(std::string path);
private:
	Vector2D* position;
	int width, height;
	int state;

	void (*callback)();

	Color color;

	SDL_Rect rect;
	SDL_Texture* texture;
};

#endif // MENUBUTTON_H
