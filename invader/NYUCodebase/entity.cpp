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
    
    //    <SubTexture name="block.png" x="106" y="77" width="28" height="28"/>
    //    <SubTexture name="enemy1.png" x="0" y="77" width="104" height="84"/>
    //    <SubTexture name="enemy2.png" x="0" y="163" width="103" height="84"/>
    //    <SubTexture name="enemy3.png" x="105" y="163" width="103" height="84"/>
    //    <SubTexture name="enemybullet.png" x="106" y="116" width="9" height="37"/>
    //    <SubTexture name="player.png" x="0" y="0" width="112" height="75"/>
    //    <SubTexture name="playerbullet.png" x="106" y="77" width="9" height="37"/>
    float player[] = {0.0, 0.0, 115.0, 75.0};
    float enemy1[] = {0.0, 77.0, 104.0, 84.0};
    float enemy2[] = {0.0, 163.0, 103.0, 84.0};
    float enemy3[] = {105.0, 163.0, 103.0, 84.0};
    float block[] = {106.0, 77.0, 28.0, 28.0};
    
    float xcoord = 0;
    float ycoord = 0;
    float wspec = 0;
    float hspec = 0;

    if (active == true) { //Draw if still alive
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
        
        else if(type == 4){
            xcoord = block[0]/256.0;
            ycoord = block[1]/256.0;
            wspec = block[2]/256.0;
            hspec = block[3]/256.0;
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
}

bool Entity::checkWallCollision(){
    if ((xpos < -0.9 or xpos > 0.9) && active == true){
        return true;
    }
    else{
        return false;
    }
}

void Entity::moveLeft(float elapsed){
    if (xpos >= -0.9){
        xpos -= elapsed;
    }
}

void Entity::moveRight(float elapsed){
    if (xpos <= 0.9) {
        xpos += elapsed;
    }

}

void Entity::reverseAIMove(){
    if (xpos <= -0.9){
        xpos = -0.9;
    }
    else if (xpos > 0.9){
        xpos = 0.9;
    }
    xdir *= -1.0;
    ypos -= 0.02;
}

void Entity::AIMove(float elapsed){
    checkWallCollision();
    xpos += elapsed * 0.3 * xdir;
    
}

float Entity::getXPos(){
    return xpos;
}

float Entity::getYPos(){
    return ypos;
}

float Entity::getHeight(){
    return height;
}

float Entity::getWidth(){
    return width;
}

void Entity::hitpointMod(int damage){
    hitpoints += damage;
}

int Entity::getHP(){
    return hitpoints;
}

void Entity::destroyEntity(){
    active = false;
}

bool Entity::isActive(){
    return active;
}