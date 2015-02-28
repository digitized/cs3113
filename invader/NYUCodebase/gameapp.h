//
//  gameapp.h
//  NYUCodebase
//
//  Created by Alexander Lee on 2/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__gameapp__
#define __NYUCodebase__gameapp__

#include <stdio.h>

#endif /* defined(__NYUCodebase__gameapp__) */
#include "entity.h"
#include <vector>
#include "string"
using namespace std;


class GameApp{
public:
    GameApp();
    ~GameApp();
    
    void Init();
    void Render();
    void RenderMenu();
    void RenderGame();
    void UpdateMenu();
    void UpdateGame();
    void Update(float elapsed);
    bool UpdateAndRender();
    
    void initializeAssets();
    
    GLuint LoadTexture(const char *image_path, GLenum format);
    void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a);
    void DrawEntity();
private:
    int state;
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    vector<Entity> Entities;
    GLuint font;
    GLuint sprites;
    int entityType;
    const Uint8 *keys;
};