//
//  entity.cpp
//  NYUCodebase
//
//  Created by Alexander Lee on 3/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "entity.h"

Entity::Entity(float x, float y, float w, float h){
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    velocity_x = 0;
    velocity_y = 0;
    accel_x = 0;
    accel_y = 0;
    onFloor = true;
}

float Entity::getX(){
    return xpos;
}

float Entity::getY(){
    return ypos;
}

void Entity::hasCollided(Entity &platform) {
    float playerLeft = xpos - width*0.5;
    float playerRight = xpos + width*0.5;
    float playerTop = ypos + height*0.5;
    float playerBottom = ypos - height*0.5;
    float platLeft = platform.getX() - platform.getWidth()*0.5;
    float platRight = platform.getX() + platform.getWidth()*0.5;
    float platTop = platform.getY() + platform.getHeight()*0.5;
    float platBottom = platform.getY() - platform.getHeight()*0.5;
    
    float diffLeft = playerLeft - platRight;
    float diffRight = playerRight - platLeft;
    float diffTop = playerTop - platBottom;
    float diffBottom = playerBottom - platTop;
    
    //Check walls
    if (playerLeft <= -1.0) {
        xpos = -1.0 + width*0.5;
        if (velocity_x < 0) {
            velocity_x = 0;
            accel_x = 0;
        }
        
    }
    if (playerRight >= 1.0) {
        xpos = 1.0 - width*0.5;
        if (velocity_x > 0) {
            velocity_x = 0;
            accel_x = 0;
        }
    }
    
    
    //Left Collision Check
    if (playerLeft <= platRight && playerLeft >= platLeft){
        // Top / Left
        if (playerTop >= platBottom && playerTop <= platTop) {
            if (diffLeft <= diffTop) {
                //Collide Left
                if (velocity_x < 0){
                    velocity_x = 0;
                    accel_x = 0;
                }
                onFloor = false;
            }
            else {
                //Collide Top
                if (velocity_y > 0) {
                    velocity_y = 0;
                    accel_y = 0;
                }
            }
            
        }
        // Bottom / Left
        else if (playerBottom <= platTop && playerBottom >= platBottom) {
            
            
            //Collide Left
            if (diffLeft <= diffBottom){
                if (velocity_x < 0){
                    velocity_x = 0;
                    accel_x = 0;
                }
                onFloor = false;
            }
            
            //Collide Bottom
            else {
                onFloor = true;
                ypos = platTop + height*0.5;
                if (velocity_y < 0){
                    velocity_y = 0;
                    accel_y = 0;
                }
            }
        }
    }
    
    //Right Collision Check
    if (playerRight >= platLeft && playerRight <= platRight){
        // Top / Right
        if (playerTop >= platBottom && playerTop <= platTop) {
            if (diffRight <= diffTop) {
                //Collide Right
                if (velocity_x > 0){
                    velocity_x = 0;
                    accel_x = 0;
                }
                onFloor = false;
            }
            else {
                //Collide Top
                if (velocity_y > 0) {
                    velocity_y = 0;
                    accel_y = 0;
                }
            }
            
        }
        // Bottom / Right
        else if (playerBottom <= platTop && playerBottom >= platBottom) {
            //Collide Left
            if (diffRight <= diffBottom){
                if (velocity_x > 0){
                    velocity_x = 0;
                    accel_x = 0;
                }
                onFloor = false;
            }
            
            //Collide Bottom
            else {
                onFloor = true;
                ypos = platTop + height*0.5;
                if (velocity_y < 0){
                    velocity_y = 0;
                    accel_y = 0;
                }
            }
        }

    }
    
    

}

void Entity::updateFloor(bool floor){
    onFloor = floor;
}

void Entity::updateYSpeed(float elapsed){
    
    if (!onFloor) {
        accel_y -= 10.0 * elapsed;
        velocity_y += accel_y;
        xpos += velocity_y;
    }
    else {
        accel_y = -2.3;
    }
}

//Jump function
void Entity::jump(float elapsed){
    if (onFloor) {
        accel_y = 1.2;
        onFloor = false;
    }
}

float Entity::getHeight(){
    return height;
}

float Entity::getWidth(){
    return width;
}

void Entity::moveX(float x){
    accel_x = 0.02*x;
    
}

void Entity::moveY(float y){
    ypos += y;
}

void Entity::DrawSpritePlayer(GLint texture, GLint textureJump) {
    glEnable(GL_TEXTURE_2D);
    if (onFloor)
        glBindTexture(GL_TEXTURE_2D, texture);
    else
        glBindTexture(GL_TEXTURE_2D, textureJump);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(xpos, ypos, 0.0);
    
    GLfloat quad[] = {-0.5f*width, 0.5f*height, -0.5f*width, -0.5f*height, 0.5f*width, -0.5f*height, 0.5f*width, 0.5f*height};
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

void Entity::DrawTileSprite(GLint texture, int index) {
    float h = 13.0;
    float w = 13.0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(xpos, ypos, 0.0);
    
    GLfloat quad[] = {-0.5f*width, 0.5f*height, -0.5f*width, -0.5f*height, 0.5f*width, -0.5f*height, 0.5f*width, 0.5f*height};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {index/w, index/h, index/w, (index+1)/h, (index+1)/w, (index+1)/h, (index+1)/w, index/h};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}



void Entity::update(float elapsed){
    //Y Movement

    ypos += velocity_y * elapsed;
    accel_y -= gravity * elapsed;
    velocity_y += accel_y * elapsed;

    
    //X Movement
    velocity_x += accel_x;
    xpos += velocity_x;
    
    if (accel_x > 0) {
        accel_x -= friction*elapsed;
    }
    else if (accel_x < 0){
        accel_x += friction*elapsed;
    }
    
    if (velocity_x >= 0) {
        if  (accel_x + velocity_x > 0){
            velocity_x += accel_x;
        }
        else {
            velocity_x = 0;
            accel_x = 0;
        }
    }
    else if (velocity_x <= 0) {
        if  (accel_x + velocity_x < 0){
            velocity_x += accel_x;
        }
        else {
            velocity_x = 0;
            accel_x = 0;
        }
    }
}


