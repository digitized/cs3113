
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "gameapp.h"
#include "string"

int main(int argc, char *argv[])
{
    GameApp game;
    while(!game.UpdateAndRender()){};
	return 0;
}