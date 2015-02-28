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
    if (spriteType >= 1 and spriteType <= 3) {
        xdir = 1.0;
    }
    
}


void Entity::DrawSprite(GLint texture) {
    float spriteSheetSize = 256.0;
    float player[] = {0.0, 0.0, 115.0, 75.0};
    float enemy1[] = {0.0, 77.0, 104.0, 84.0};
    float enemy2[] = {0.0, 163.0, 103.0, 84.0};
    float enemy3[] = {105.0, 163.0, 103.0, 84.0};
    
    float xcoord = 0;
    float ycoord = 0;
    float wspec = 0;
    float hspec = 0;
    
//    <SubTexture name="enemy1.png" x="0" y="77" width="104" height="84"/>
//    <SubTexture name="enemy2.png" x="0" y="163" width="103" height="84"/>
//    <SubTexture name="enemy3.png" x="105" y="163" width="103" height="84"/>
//    <SubTexture name="enemybullet.png" x="106" y="116" width="9" height="37"/>
//    <SubTexture name="player.png" x="0" y="0" width="112" height="75"/>
//    <SubTexture name="playerbullet.png" x="106" y="77" width="9" height="37"/>
    
    if (type == 0){
        xcoord = player[0]/256.0;
        ycoord = player[1]/256.0;
        wspec = player[2]/256.0;
        hspec = player[3]/256.0;
    }
    else if(type == 1){
        xcoord = enemy1[0]/256.0;
        ycoord = enemy1[1]/256.0;
        wspec = enemy1[2]/256.0;
        hspec = enemy1[3]/256.0;
    }

    else if(type == 2){
        xcoord = enemy2[0]/256.0;
        ycoord = enemy2[1]/256.0;
        wspec = enemy2[2]/256.0;
        hspec = enemy2[3]/256.0;
    }

    
    else if(type == 3){
        xcoord = enemy3[0]/256.0;
        ycoord = enemy3[1]/256.0;
        wspec = enemy3[2]/256.0;
        hspec = enemy3[3]/256.0;
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

bool Entity::checkWallCollision(){
    if (xpos < -1.25 or xpos > 1.25){
        return true;
    }
    else{
        return false;
    }
}

void Entity::moveLeft(float elapsed){
    if (xpos >= -1.25){
        xpos -= elapsed;
    }
}

void Entity::moveRight(float elapsed){
    if (xpos <= 1.25) {
        xpos += elapsed;
    }

}

void Entity::reverseAIMove(){
    xdir *= -1.0;
}

void Entity::AIMove(float elapsed){
    checkWallCollision();
    xpos += elapsed * 0.3 * xdir;
    
}