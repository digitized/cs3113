//
//  bullet.cpp
//  NYUCodebase
//
//  Created by Alexander Lee on 2/28/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "bullet.h"

Bullet::Bullet(float x, float y, float w, float h, int s){
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    source = s;
    active = false;
}

void Bullet::Shoot(float x, float y, int s)
{
    xpos = x;
    ypos = y+0.15;
    source = s;
    active = true;
}

bool Bullet::isActive(){
    return active;
}

void Bullet::updateBullet(float elapsed, std::vector<Entity> *entities){
    if (active == true) {
        ypos += elapsed * 0.3;
    }
    if (ypos >= 1.0 || ypos <= -1.0){
        active = false;
    }
    if (active){
        for (int eIndex = 0; eIndex < 19; eIndex++){
            if ((*entities)[eIndex].isActive()){
                float bulletTop = ypos+0.5*height;
                float bulletBottom = ypos-0.5*height;
                float bulletLeft = xpos - 0.5*width;
                float bulletRight = xpos + 0.5*width;
                
                float entityTop = (*entities)[eIndex].getYPos()+0.5*(*entities)[eIndex].getHeight();
                float entityBottom = (*entities)[eIndex].getYPos()-0.5*(*entities)[eIndex].getHeight();
                float entityLeft = (*entities)[eIndex].getXPos()-0.5*(*entities)[eIndex].getWidth();
                float entityRight = (*entities)[eIndex].getXPos()+0.5*(*entities)[eIndex].getWidth();
                
                //Check Collision
                if((bulletTop > entityBottom and bulletTop < entityTop) || (bulletBottom > entityBottom and bulletBottom < entityTop)){
                    if (bulletLeft < entityRight && bulletLeft > entityLeft){
                        active = false;
                        (*entities)[eIndex].hitpointMod(-1);
                        if ((*entities)[eIndex].getHP() <= 0){
                            (*entities)[eIndex].destroyEntity();
                        }
                        
                    }
                    else if (bulletRight > entityLeft && bulletRight < entityRight){
                        active = false;
                        (*entities)[eIndex].hitpointMod(-1);
                        if ((*entities)[eIndex].getHP() <= 0){
                            (*entities)[eIndex].destroyEntity();
                        }
                    }
                }
            }
        }
    }
}

void Bullet::DrawBullet(GLint texture){
//    <SubTexture name="enemybullet.png" x="106" y="107" width="9" height="37"/>
//    <SubTexture name="player.png" x="0" y="0" width="112" height="75"/>
//    <SubTexture name="playerbullet.png" x="114" y="0" width="9" height="37"/>
    float playerBullet[] = {114.0, 0.0, 9.0, 37.0};
    float enemyBullet[] = {106.0, 107.0, 9.0, 37.0};
    
    float xcoord = 0;
    float ycoord = 0;
    float wspec = 0;
    float hspec = 0;

    if (source == 0){
        xcoord = playerBullet[0]/256.0;
        ycoord = playerBullet[1]/256.0;
        wspec = playerBullet[2]/256.0;
        hspec = playerBullet[3]/256.0;
    }
    else if(source == 1){
        xcoord = enemyBullet[0]/256.0;
        ycoord = enemyBullet[1]/256.0;
        wspec = enemyBullet[2]/256.0;
        hspec = enemyBullet[3]/256.0;
    }
    
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(xpos, ypos, 0.0);
    
    GLfloat quad[] = {width*-0.5f, height*0.5f, width*-0.5f, height*-0.5f, width*0.5f, height*-0.5f, width*0.5f, height*0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {xcoord, ycoord, xcoord, ycoord + hspec, xcoord+wspec, ycoord+hspec, xcoord+wspec, ycoord};
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);

}



