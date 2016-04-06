
#ifndef __tinyrender__window__
#define __tinyrender__window__

#include <SDL/SDL.h>
#include "canvas.h"

class Window {

	int _width;
	int _height;
	SDL_Surface *_screen;

	Canvas *canvas;

public:
	Window(int width = 600, int height = 800, const char *title = "tinyRender");
	virtual ~Window();

	void run();
};

#endif
