//
//  Entity.h
//  NYUCodebase
//
//  Created by Alexander Lee on 2/26/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h


#endif

class Entity{
public:
    Entity(float x, float y, float w, float h, int hp, int spriteType);
    
    void DrawSprite(GLint texture);
    void moveLeft(float elapsed);
    void moveRight(float elapsed);
    void AIMove(float elapsed);
    void reverseAIMove();
    bool checkWallCollision();
    float getXPos();
    float getYPos();
    
private:
    int hitpoints;
    int type;
    
    float height;
    float width;
    float xpos;
    float ypos;
    float xdir;
    float ydir;
    
    bool collisionTop;
    bool collisionBottom;
    bool collisionLeft;
    bool collisionRight;
    bool active;
};
