//
//  bullet.h
//  NYUCodebase
//
//  Created by Alexander Lee on 2/28/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//
#pragma once
#include "entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#ifndef NYUCodebase_bullet_h
#define NYUCodebase_bullet_h


#endif

#include <vector>


class Bullet{
public:
    Bullet(float x, float y, float w, float h, int source);
    bool isActive();
    
    void Shoot(float x, float y, int s);
    
    void EnemyShoot(float x, float y, int s);
    
    void DrawBullet(GLint texture);
    
    void updateBullet(float elapsed, std::vector<Entity>* entities, int* numEnemy);
private:
    bool active;
    float xpos;
    float ypos;
    float width;
    float height;
    int source;
};