#include "window.h"

bool Window::running = false;
SDL_Renderer* Window::renderer = NULL;
SDL_Window* Window::window = NULL;
AppStateMachine* Window::appStateMachine = NULL;

Window::Window(int width_, int height_) : width(width_), height(height_) {
	window = NULL;
	renderer = NULL;
	if(!init()) { exit(1); }
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) { return false; }
	// Linear texture filtering
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) { return false; }

	window = SDL_CreateWindow("Visual Alg", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_SHOWN);
	if(window == NULL) { return false; }

	// Vsync renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x53, 0xAA, 0xFF);
	
	if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) { return false; }

	running = true;

	appStateMachine = new AppStateMachine();

	appStateMachine->changeState(new MainMenuState());

	return true;
}

void Window::render() {
	SDL_RenderClear(renderer);

	appStateMachine->render();

	SDL_RenderPresent(renderer);
}

void Window::update() {
	appStateMachine->update();
}


void Window::handleEvents() {
	InputHandler::Instance()->update();
}

void Window::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
