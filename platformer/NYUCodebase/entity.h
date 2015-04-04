//
//  entity.h
//  NYUCodebase
//
//  Created by Alexander Lee on 3/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__entity__
#define __NYUCodebase__entity__

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdio.h>

#endif /* defined(__NYUCodebase__entity__) */
class Entity {
    
public:
    Entity(float x, float y, float w, float h);
    void updateYSpeed(float elapsed);
    float getX();
    float getY();
    float getHeight();
    float getWidth();
    void jump(float elapsed);
    void DrawSpritePlayer(GLint texture, GLint textureJump);
    void DrawTileSprite(GLint texture, int index);
    void moveX(float x);
    void moveY(float y);
    void update(float elapsed);
    void hasCollided( Entity & platform);
    void updateFloor(bool floor);
    
private:
    float xpos;
    float ypos;
    
    float gravity = 1.5;
    float friction = 5.0;
    float width;
    float height;
    
    float velocity_x;
    float velocity_y;
    
    float accel_x;
    float accel_y;
    
    bool onFloor;
    
};
