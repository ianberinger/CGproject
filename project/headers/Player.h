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
    typedef Entity super;
    Player(float x, float y, float z, float w, float h, float l, bool col);
    ~Player();
    
};

#endif /* Player_h */



