#include "entity.h"

Entity::Entity(float x, float y, float w, float h, int hp, int spriteType){
    xpos = x;
    ypos = y;
    width = w;
    height = h;
    active = true;
    hitpoints = hp;
    ydir = 0.0;
    xdir = 0.0;
    type = spriteType;
    collisionBottom = false;
    collisionLeft = false;
    collisionRight = false;
    collisionTop = false;
    
}


void Entity::DrawSprite(GLint texture) {
    float spriteSheetSize = 256.0;
    float player[4] = {0.0, 0.0, 115.0, 75.0};
    
    float xcoord = 0;
    float ycoord = 0;
    float wspec = 0;
    float hspec = 0;
    
    if (type == 0){
        xcoord = player[0]/256.0;
        ycoord = player[1]/256.0;
        wspec = player[2]/256.0;
        hspec = player[3]/256.0;
    }
    
    

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(xpos, ypos, 0.0);
    
    GLfloat quad[] = {width*-0.5f, height*0.5f, width*-0.5f, height*-0.5f, width*0.5f, height*-0.5f, width*0.5f, height*0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
//    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    GLfloat quadUVs[] = {xcoord, ycoord, xcoord, ycoord + hspec, xcoord+wspec, ycoord+hspec, xcoord+wspec, ycoord};
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
}