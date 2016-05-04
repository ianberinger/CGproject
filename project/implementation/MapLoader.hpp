//
//  MapLoader.hpp
//  bRenderer_ios
//
//  Created by Ian Beringer on 5/4/16.
//
//

#ifndef MapLoader_hpp
#define MapLoader_hpp

#include <cmath>

enum markerDirection {UP, DOWN, LEFT, RIGHT};

struct marker {
    bool isValid;
    int z;
    int x;
    float angle;
    markerDirection direction;
};

struct marker identifyMarker(int map[50][50], int i,int j);

#endif /* MapLoader_hpp */
