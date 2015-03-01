#include "gameapp.h"

GameApp::GameApp(){
    Init();
    done = false;
    lastFrameTicks = 0.0f;
    state = 1;
    keys = SDL_GetKeyboardState(NULL);
    
}

GameApp::~GameApp(){
    SDL_Quit();
}

void GameApp::Init(){
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glViewport(0, 0, 800, 600);

    glMatrixMode(GL_MODELVIEW);
    
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    font = LoadTexture("font1.png", GL_RGBA);
    sprites = LoadTexture("sprites.png", GL_RGBA);
    initializeAssets();
}
//WIN
void GameApp::RenderWin(){
    glLoadIdentity();
    glTranslatef(-0.4f, 0.5f, 0.0f);
    GameApp::DrawText(font, "YOU WIN", 0.1f, 0.01f, 1.0f, 1.0f, 1.0f, 1.0f);
    SDL_GL_SwapWindow(displayWindow);
}

//LOSS
void GameApp::RenderLoss(){
    glLoadIdentity();
    glTranslatef(-0.4f, 0.5f, 0.0f);
    GameApp::DrawText(font, "YOU LOSE", 0.1f, 0.01f, 1.0f, 1.0f, 1.0f, 1.0f);
    SDL_GL_SwapWindow(displayWindow);
}

////RENDER
void GameApp::Render(){
    glClear(GL_COLOR_BUFFER_BIT);
    switch(state){
        case 0:
            RenderMenu();
            break;
        case 1:
            RenderGame();
            break;
        case 2:
            RenderWin();
            break;
        case 3:
            RenderLoss();
            break;
    }
    
}


void GameApp::RenderMenu(){
    glLoadIdentity();
    glTranslatef(-0.4f, 0.5f, 0.0f);
    GameApp::DrawText(font, "Main Menu", 0.1f, 0.01f, 1.0f, 1.0f, 1.0f, 1.0f);
    
    glLoadIdentity();
    glTranslatef(-0.4f, 0.2f, 0.0f);
    GameApp::DrawText(font, "Press Enter to Start", 0.1f, 0.01f, 0.0f, 0.0f, 0.0f, 1.0f);
    SDL_GL_SwapWindow(displayWindow);
}

void GameApp::RenderGame(){
    GameApp::DrawEntity();
    DrawBullets();
    SDL_GL_SwapWindow(displayWindow);
}

////UPDATE
void GameApp::UpdateMenu(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true; }
    }
    if(keys[SDL_SCANCODE_RETURN]) {
        state = 1;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    }

}

void GameApp::EnemyFire(){
    int bulletSlot = 4;
    
    for (int b = 0; b < 5 && b != 4; b++){
        if (Bullets[b].isActive() == false){
            bulletSlot = b;
            break;
        }
    }
    int enemyNum = fmod(enemyTimer * 1000, 15)+1;
    Bullets[bulletSlot].EnemyShoot(Entities[enemyNum].getXPos(), Entities[enemyNum].getYPos(), 1);
}

void GameApp::UpdateGame(float elapsed){
    shootTimer += elapsed;
    enemyTimer += elapsed;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true; }
        //Player Shooting
        else if(keys[SDL_SCANCODE_SPACE]) { // Shoot
            if (shootTimer > 0.3){
                GameApp::PlayerFire();
                shootTimer = 0;
            }
            
        }
    }
    if(keys[SDL_SCANCODE_LEFT]) {         // Move Left
        Entities[0].moveLeft(elapsed);
    } else if(keys[SDL_SCANCODE_RIGHT]) { // Move Right
        Entities[0].moveRight(elapsed);
    }
    
    //Enemy Shooting AI
    if (enemyTimer >= 1.0) {
        EnemyFire();
        enemyTimer = 0;
    }
    
    //Check enemy side wall collision
    bool hasCollided = false;
    for(int enemy = 1; enemy < 16; enemy++){
        if(Entities[enemy].checkWallCollision()){
            hasCollided = true;
        }
    }
    if (hasCollided){
        for(int enemy = 1; enemy < 16; enemy++){
                Entities[enemy].reverseAIMove();
        }
    }
    for(int enemy = 1; enemy < 16; enemy++){
        Entities[enemy].AIMove(elapsed);
    }
    for(int bulletIndex = 0; bulletIndex < 10; bulletIndex++){
        Bullets[bulletIndex].updateBullet(elapsed, &Entities, &numEnemy);
    }
    //Player wins
    if (numEnemy <= 0) {
        state = 2;
    }
    //Player loss
    if (Entities[0].getHP() <= 0) {
        state = 3;
    }
    
}
void GameApp::Update(float elapsed){
    switch (state){
        case 0:
            UpdateMenu();
            break;
        case 1:
            UpdateGame(elapsed);
            break;
    }

}

bool GameApp::UpdateAndRender(){
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    
    lastFrameTicks = ticks;
    Update(elapsed);
    Render();
    return done;
}
void GameApp::PlayerFire(){
    int bulletSlot = -1;
    
    for (int b = 0; b < 5 && b != -1; b++){
        if (Bullets[b].isActive() == false){
            bulletSlot = b;
            break;
        }
    }
    Bullets[bulletSlot].Shoot(Entities[0].getXPos(), Entities[0].getYPos(), 0);
}
void GameApp::initializeAssets(){
    //Initialize enemies
    //0 = player
    //1 - 15 = enemies
    //16 - 18 = Blocks
    
    //Player
    Entities.push_back(Entity(0.0, -0.9, 0.15, 0.15, 1, 0));
    
    //Enemies
    for(int rows = 0; rows < 3; rows++){
        for(int num = 0; num < 5; num++){
            Entities.push_back(Entity(-0.7+num*0.3, 0.8-rows*0.2, 0.15, 0.15, 3-rows, 3 - rows));
        }
    }
    //Blocks
    for(int blocks = 0; blocks < 3; blocks++){
        Entities.push_back(Entity(-0.65+blocks*0.7, -0.5, 0.3,0.3, 5, 4));
    }
    
    //Bullets
    for (int b = 0; b < 10; b++){
        Bullets.push_back(Bullet(0.0, 0.0, 0.03, 0.06, 0));
    }

}

GLuint GameApp::LoadTexture(const char *image_path, GLenum format) {
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

void GameApp::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a) {
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float texture_size = 1.0/16.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
    }
    glColorPointer(4, GL_FLOAT, 0, colorData.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawArrays(GL_QUADS, 0, text.size() * 4);
    glDisableClientState(GL_COLOR_ARRAY);
}

void GameApp::DrawEntity(){
    for(int i = 0; i < 19; i++){
        Entities[i].DrawSprite(sprites);
    }
//    Entities[0].DrawSprite(sprites);
//    Entities[1].DrawSprite(sprites);
}

void GameApp::DrawBullets(){
    for(int b = 0; b < 10; b++){
        if(Bullets[b].isActive()){
            Bullets[b].DrawBullet(sprites);
        }
    }
}

