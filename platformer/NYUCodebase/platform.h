//
//  platform.h
//  NYUCodebase
//
//  Created by Alexander Lee on 3/31/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__platform__
#define __NYUCodebase__platform__

#include <vector>
#include <string>
#include "entity.h"
#include <stdio.h>

using namespace std;

#endif /* defined(__NYUCodebase__platform__) */

class Platform{
public:
    Platform();
    ~Platform();
    void setup();
    void init();
    void run();
    void update();
    void render();
    void collisionCheck();
    GLuint LoadTexture(const char *image_path, GLenum format);
    void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY, float width, float height, int repeat);
    void DrawPlatform(int texture, int index, float size, float spacing, int repeat);
    void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a);
    void renderGoal();
    void renderFinish();
    void checkGoal();
    
private:
    vector<Entity> entities;
    float lastFrameTicks = 0.0f;
    const Uint8 *keys;
    SDL_Window* displayWindow;
    SDL_Event event;
    GLuint player;
    GLuint playerJump;
    GLuint platform;
    GLuint text;
    bool goal = false;
    bool done = false;
    
};