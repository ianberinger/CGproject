//
//  Enitity.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 20.04.16.
//
//



#ifndef Enitity_h
#define Enitity_h


#include <iostream>
#include <string>
#include "Renderer.h"



class Entity{
    
public:
    
    enum Type {NOTCOLLIDABLE, COLLIDABLE, RAMP};
    
    Entity(float x, float y, float z, float w, float h, float l, bool col, Type type){
        setX(x);
        setY(y);
        setZ(z);
        setWidth(w);
        setHeight(h);
        setLength(l);
        setCollision(col);
        setType(type);
    }
    
    
    
    virtual ~Entity(){}
    
    const vmml::Vector4f fogColor = vmml::Vector4f(0.5, 0.5, 0.5, 1);

    
    
    void setX(float x1){x=x1;}
    void setY(float y1){y=y1;}
    void setZ(float z1){z=z1;}
    
    void setWidth(float w){width=w;};
    void setHeight(float h){height=h;}
    void setLength(float l){length=l;}
    
    void setType(Type t){ type = t; };
    
    void setCollision(bool col){collision=col;}
    
    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}
    vmml::Vector3f getXYZ() const {return vmml::Vector3f(x,y,z);}
    
    float getWidth() const {return width;}
    float getHeight() const {return height;}
    float getLength() const {return length;}
    
    bool hasCollision(){return collision;}

    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix)=0;
    virtual void update(Renderer &r, const vmml::Vector3f &collisionForce)=0;
    
    Type getType() const { return type; };
    
private:
   float x;
   float y;
    float z;
    float width;
    float height;
    float length;
    Type type;

    bool collision;
    
};


#endif /* Enitity_h */







