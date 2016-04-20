//
//  Enitity.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 20.04.16.
//
//

#ifndef Enitity_h
#define Enitity_h
#endif /* Enitity_h */

#include <iostream>
#include <string>
#include <stdio>

class Enitity {

public:
    Player(float x, float y, float z, float w, float h, float l);
    
    void setX(float x1){x=x1;}
    void setY(float y1){y=y1;}
    void setZ(float z1){z=z1;}
    
    void setWidth(float w){width=w;};
    void setHeight(float h){height=h;}
    void setLength(float l){length=l;}
    
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    
    float getWidth(){return width;}
    float getHeight(){return height;}
    float getLength(){return length;}

private:
    float x;
    float y;
    float z;
    float width;
    float height;
    float length;
    
}