
#include "mesh.h"
#include "window.h"

int main(int argc, char **argv)
{
	Mesh mesh("test.ply", NULL);
	Window *window = new Window();

	window->run();
	getchar();
	delete window;

	return 0;
}
