//
//  platform.cpp
//  NYUCodebase
//
//  Created by Alexander Lee on 3/31/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "platform.h"

void Platform::setup(){
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Platform::init(){
    player = LoadTexture("pieceWhite_border05.png", GL_RGBA);
    platform = LoadTexture("tiles_spritesheet.png", GL_RGBA);
    playerJump = LoadTexture("pieceWhite_border06.png", GL_RGBA);
    text = LoadTexture("font1.png", GL_RGBA);
    entities.push_back(Entity(0, 0, 0.1, 0.1));
    
    
    for (int i = 0; i < 27; i++){
        entities.push_back(Entity(-1.3+0.1*i, -0.6, 0.1, 0.1));
    }
    
    for (int i = 0; i < 3; i++){
        entities.push_back(Entity(-0.6+0.1*i, -0.2, 0.1, 0.1));
    }
    
    for (int i = 0; i < 3; i++){
        entities.push_back(Entity(-0.2+0.1*i, 0.2, 0.1, 0.1));
    }
    
    for (int i = 0; i < 3; i++){
        entities.push_back(Entity(0.0+0.1*i, 0.6, 0.1, 0.1));
    }
}


GLuint Platform::LoadTexture(const char *image_path, GLenum format) {
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
void Platform::DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY, float width, float height, int repeat) {
    // our regular sprite drawing
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture );
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    GLfloat quad[] = {width*-0.5f, height*0.5f, width*-0.5f, height*-0.5f, width*0.5f, height*-0.5f, width*0.5f, height*0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,
        
        u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v };
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);    // our regular sprite drawing
}

void Platform::DrawPlatform(int texture, int index, float size, float spacing, int repeat) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    
    float texture_size = 1.0/13.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    for(int i=0; i < repeat; i++) {
        float texture_x = (float)(index % 13) / 13.0f;
        float texture_y = (float)(index / 13) / 13.0f;
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
    }
    
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawArrays(GL_QUADS, 0, repeat * 4);
}

void Platform::run(){
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        update();
        render();
    }
}

void Platform::update(){
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(keys[SDL_SCANCODE_SPACE]){ //Jump
        entities[0].jump(elapsed);
    } else if(keys[SDL_SCANCODE_LEFT]){
        entities[0].moveX(-1.0);
    }
    
    if(keys[SDL_SCANCODE_RIGHT]){
        entities[0].moveX(1.0);
    }
    entities[0].update(elapsed);
    collisionCheck();
    checkGoal();
    
}

void Platform::checkGoal() {
    if (entities[0].getX() > 0.0 && entities[0].getX() < 0.3){
        if (entities[0].getY() > 0.6){
            goal = true;
        }
        else
            goal = false;
    }
    else
        goal = false;
}

void Platform::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a) {
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

void Platform::renderGoal(){
    glTranslatef(-0.25, 0.15, 0);
    DrawText(text, "GOAL", 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void Platform::renderFinish(){
    glTranslatef(-0.45, 0.15, 0);
    DrawText(text, "YOU WIN!", 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void Platform::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    entities[0].DrawSpritePlayer(player, playerJump);
    for (int i = 1; i < entities.size();i++){
        entities[i].DrawTileSprite(platform, 2);
    }
    if (!goal){
        renderGoal();
    }
    else {
        renderFinish();
    }

    SDL_GL_SwapWindow(displayWindow);
    
}

Platform::Platform(){
    setup();
    init();
}


Platform::~Platform(){
    SDL_Quit();
}

void Platform::collisionCheck(){
    for (int i = 1; i < entities.size(); i++){
        entities[0].hasCollided(entities[i]);
    }
}