
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;
class Entity{
public:
    //Constructor
    Entity(float xcoord, float ycoord, float w, float h){
        x = xcoord;
        y = ycoord;
        width = w;
        height = h;
    }
    float x;
    float y;
    float rotation = 0.0;
    
    float width;
    float height;
    
    float speed = 0.2;
    float direction_x = 0.0;
    float direction_y = 0.0;
    void draw(){
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glTranslatef(x, y, 0.0);
        GLfloat quad[] = {width*-0.5f, height*0.5f, width*-0.5f, height*-0.5f, width*0.5f, height*-0.5f, width*0.5f, height*0.5f};
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_QUADS, 0, 4);
        
    }
    
};

void setup(){
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
}

void update(Entity *ball, Entity *player1, Entity *player2, float elapsed, const Uint8 *keys){
    if(keys[SDL_SCANCODE_W]) {
        if(player1->y+(player1->height*0.5) <= 1.0){
            player1->y += elapsed;
        }
    } else if(keys[SDL_SCANCODE_S]) {
        if(player1->y-(player1->height*0.5) >= -1.0){
            player1->y -= elapsed;
        }
    }
    
    if(keys[SDL_SCANCODE_UP]) {
        if(player2->y+(player2->height*0.5) <= 1.0){
            player2->y += elapsed;
        }
    } else if(keys[SDL_SCANCODE_DOWN]) {
        if(player2->y-(player2->height*0.5) >= -1.0){
            player2->y -= elapsed;
        }
    }

    ball->x += elapsed*ball->direction_x;
    ball->y += elapsed*ball->direction_y;
    
    if (ball->x-(ball->width*0.5) <= player1->x+(player1->width*0.5) && ball->y <= player1->y + (player1->height*0.5) && ball->y >= player1->y - (player1->height*0.5)){
        ball->direction_x *= -1.0;
    }
    else if (ball->x-(ball->width*0.5) <= player1->x+(player1->width*0.5) && ball->y <= player1->y + (player1->height*0.5) && ball->y >= player1->y - (player1->height*0.5)){
        ball->direction_x *= -1.0;
    }
    else if (ball->x+(ball->width*0.5) >= player2->x-(player2->width*0.5) && ball->y <= player2->y + (player2->height*0.5) && ball->y >= player2->y - (player2->height*0.5)){
        ball->direction_x *= -1.0;
    }
    else if (ball->x+(ball->width*0.5) >= player2->x-(player2->width*0.5) && ball->y <= player2->y + (player2->height*0.5) && ball->y >= player2->y - (player2->height*0.5)){
        ball->direction_x *= -1.0;
    }
    else if (ball->x >= 1.33 || ball->x <= -1.33){ //Ball Out of Bounds
        if (ball->x >= 1.33){ //Player 1 win red
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        if (ball->x <= -1.33){ //Player 2 win blue
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        }
        ball->x = 0;
        ball->y = 0;
    }
    
    if (ball->y >= 1.0) {
        ball->direction_y *= -1.0;
    }
    else if(ball->y <= -1.0){
        ball->direction_y *= -1.0;
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(Entity *ball, Entity *player1, Entity *player2){
    //Render
    ball->draw();
    player1->draw();
    player2->draw();
}

int main(int argc, char *argv[])
{
    setup();
    
	bool done = false;
	SDL_Event event;
    
    float lastFrameTicks = 0.0f;
    
    Entity *ball = new Entity(0.0, 0.0, 0.05, 0.05);
    Entity *player1 = new Entity(-1.33, 0.0, 0.1, 0.6);
    Entity *player2 = new Entity(1.33, 0.0, 0.1, 0.6);
    
    ball->direction_x = 1.0;
    ball->direction_y = 1.0;

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
        
        float ticks = (float)SDL_GetTicks() / 1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        
        update(ball, player1, player2, elapsed, keys);
        render(ball, player1, player2);
        
        
        
		SDL_GL_SwapWindow(displayWindow);
	}
    
	SDL_Quit();
	return 0;
}