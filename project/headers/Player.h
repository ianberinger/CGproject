//
//  Player.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#ifndef Player_h
#define Player_h

#include "Entity.h"

class Player : public Entity{
public:
    Player();
    Player(float x, float y, float z, float w, float h, float l, bool col);
    
    virtual void draw();
    virtual void update();
    void setRotAngle(float ang){rotAngle=ang;}
    float getRotAngle(){return rotAngle;}
    
    void setComAngle(float ang){comAngle=ang;}
    float getComAngle(){return comAngle;}
    
    void setOffSetCam(float * off){offSetCam[0]=off[0];offSetCam[1]=off[1];offSetCam[2]=off[2];}
    float * getOffSetCam(){return offSetCam;}
    
    
private:
    float rotAngle;
    float comAngle;
    float offSetCam[3];
    
};

#endif /* Player_h */



