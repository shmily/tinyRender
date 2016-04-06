
#include <cstdio>
#include <cstring>

#include "window.h"



Window::Window(int width, int height, const char *title) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL init failed\n");
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		SDL_Quit();
		fprintf(stderr, "SDL SetVideoMode failed\n");
	}

	SDL_WM_SetCaption(title, NULL);

	this->_width  = width;
	this->_height = height;
	this->_screen = screen;

	canvas = new Canvas((uint32_t *)_screen->pixels, _width, _height);
	canvas->clear();
}

Window::~Window() {
	delete canvas;
	return;
}

void Window::run() {

	Vertex v1(Vector(0.0, 0.0, 0.0), Vector(1.0, 0.0, 0.0), 0, 0, Color::randomColor());
	Vertex v2(Vector(_width, _height, 0.0), Vector(1.0, 0.0, 0.0), 0, 0, Color::randomColor());
	Vertex v3(Vector(300, 300, 0.0), Vector(1.0, 0.0, 0.0), 0, 0, Color::randomColor());

	SDL_LockSurface(_screen);
	canvas->draw_line(v1, v2);
	canvas->draw_triangle(v1, v2, v3);

	SDL_UnlockSurface(_screen);
	SDL_UpdateRect(_screen, 0, 0, 0, 0);
	return;
}

