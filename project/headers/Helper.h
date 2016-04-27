//
//  Helper.h
//  bRenderer_ios
//
//  Created by Ian Beringer on 4/27/16.
//
//

#ifndef Helper_h
#define Helper_h

#include <cstdlib>
#include <algorithm>

class Helper {
public:
    float randomNumber(float min, float max);
    float clip(float v, float lower, float upper);
};

#endif /* Helper_h */
