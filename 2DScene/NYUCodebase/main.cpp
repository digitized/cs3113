
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;

GLuint LoadTexture(const char *image_path, GLenum format) {
    SDL_Surface *surface = IMG_Load(image_path);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    SDL_FreeSurface(surface);
    
    return textureID;
}

void DrawSprite(GLint texture, float x, float y, float xscale, float yscale, float rotation) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(xscale, yscale, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
    
	bool done = false;
	
	SDL_Event event;
    
    GLuint road = LoadTexture("roadTile6.png", GL_RGBA);
    GLuint car = LoadTexture("piecePurple_multi13.png", GL_RGBA);
    GLuint plant = LoadTexture("rpgTile175.png", GL_RGBA);
    GLuint grass = LoadTexture("rpgTile019.png", GL_RGBA);
    GLuint star = LoadTexture("starGold.png", GL_RGBA);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glClearColor(0.0f, 176.0f, 244.0f, 1.0f);
    
    float lastFrameTicks = 0.0f;
    
    
	while (!done) {
		while (SDL_PollEvent(&event)) {
            
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
        
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        GLfloat triangle[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
        glVertexPointer(2, GL_FLOAT, 0, triangle);
        glEnableClientState(GL_VERTEX_ARRAY);
        GLfloat triangleColors[] = {1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        glColorPointer(3, GL_FLOAT, 0, triangleColors);
        glEnableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_COLOR_ARRAY);
        
        glLoadIdentity();
        
        DrawSprite(road, 0.0f, 0.0f, 5.15f, 0.25f, 0.0f);
        DrawSprite(plant, 0.5f, 0.225f, 0.2f, 0.2f, 0.0f);
        DrawSprite(plant, -0.5f, 0.225f, 0.2f, 0.2f, 0.0f);
        DrawSprite(grass, 0.0f, -0.562f, 3.0f, 0.88f, 0.0f);
        DrawSprite(star, 0.7f, 0.7f, 0.3f, 0.3f, lastFrameTicks*50);
        
        float ticks = (float)SDL_GetTicks() / 1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        
        DrawSprite(car, fmod(lastFrameTicks, 2.35f)-1.17f, 0.05f, 0.5f, 0.4f, 0.0f);
        

        
        SDL_GL_SwapWindow(displayWindow);
	}
    
	SDL_Quit();
	return 0;
}