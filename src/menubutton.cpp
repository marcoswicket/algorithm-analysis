#include "menubutton.h"

MenuButton::MenuButton(void (*callback_)(), int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	position = new Vector2D(100, 100);
	width = 100;
	height = 100;
	state = MOUSE_OFF;

	rect.w = Window::getWindowWidth() * 0.30;
	rect.h = Window::getWindowHeight() * 0.13;
	rect.x = x; //rect.w * 0.35;
	rect.y = y; //Window::getWindowHeight() - rect.h - 50;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	callback = callback_;

	texture = NULL;
}

MenuButton::MenuButton(void (*callback_)(), int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int width_, int height_) {
	position = new Vector2D(100, 100);
	width = width_;
	height = height_;
	state = MOUSE_OFF;

	rect.w = width;
	rect.h = height;
	rect.x = x; //rect.w * 0.35;
	rect.y = y; //Window::getWindowHeight() - rect.h - 50;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	callback = callback_;

	texture = NULL;
}
void MenuButton::update() {
	// Check mouse collision
	Vector2D *mPos = InputHandler::Instance()->getMousePosition();

	if(state == CLICKED && !InputHandler::Instance()->getMouseButtonState(LEFT)) {
		state = MOUSE_ON;
		if(callback != NULL) callback();
	}
	if(mPos->getX() >= rect.x && mPos->getX() <= rect.x + rect.w 
			&& mPos->getY() >= rect.y && mPos->getY() <= rect.y + rect.h) {
		state = MOUSE_ON;
		if(InputHandler::Instance()->getMouseButtonState(LEFT)) {
			state = CLICKED;
		}
	} else {
		state = MOUSE_OFF;
	}

}

void MenuButton::render() {
	if(state == MOUSE_OFF) {
		SDL_SetRenderDrawColor(Window::getRenderer(), color.r, color.g, color.b, color.a);
	} else if(state == MOUSE_ON) {
		SDL_SetRenderDrawColor(Window::getRenderer(), color.r*1.2, color.g*1.2, color.b*1.2, color.a * 1.2);
	} else if (state == CLICKED) {
		SDL_SetRenderDrawColor(Window::getRenderer(), color.r*0.2, color.g*0.2, color.b*0.2, color.a);
	}

	SDL_RenderFillRect(Window::getRenderer(), &rect);

	if(texture != NULL) {
		SDL_RenderCopy(Window::getRenderer(), texture, NULL, &rect);
	} else {
		std::cout << "Texture failure" << std::endl;
	}
}

void MenuButton::loadTexture(std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) std::cout << "Loaded surface error: " << IMG_GetError() << std::endl;
	texture = SDL_CreateTextureFromSurface(Window::getRenderer(), loadedSurface);
	if(texture == NULL) std::cout << "Error on create texture: " << IMG_GetError() << std::endl;
	SDL_FreeSurface(loadedSurface);
}

void MenuButton::setTextureAlpha(int a) {
	SDL_SetTextureAlphaMod(texture, a);
}

void MenuButton::clean() {
	delete position;
	SDL_DestroyTexture(texture);
	texture = NULL;
	callback = NULL;
}
