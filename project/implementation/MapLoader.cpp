//
//  MapLoader.cpp
//  bRenderer_ios
//
//  Created by Ian Beringer on 5/4/16.
//
//

#include "MapLoader.hpp"

marker identifyMarker(int map[50][50], int i, int j) {
    int value = map[i][j];
    
    int right = map[i][j+1];
    int rightright = map[i][j+2];
    int up = map[i+1][j];
    int upup = map[i+2][j];
    
    marker res;
    
    if (right == value && rightright == value) {
        if (map[i+1][j+1] == value) {
            // 111
            // x1x
            res.isValid = true;
            res.direction = DOWN;
            res.x = i;
            res.z = j+1;
            res.angle = 3*M_PI/2;
        } else if (map[i-1][j+1] == value) {
            // x1x
            // 111
            res.isValid = true;
            res.direction = UP;
            res.x = i;
            res.z = j+1;
            res.angle = M_PI/2;
        }
    } else if (up == value && upup == value) {
        if (map[i+1][j+1] == value) {
            // 1x
            // 11
            // 1x
            res.isValid = true;
            res.direction = RIGHT;
            res.x = i + 1;
            res.z = j;
            res.angle = M_PI;
        } else if (map[i+1][j-1] == value){
            // x1
            // 11
            // x1
            res.isValid = true;
            res.direction = LEFT;
            res.x = i + 1;
            res.z = j;
            res.angle = 0.0;
        }
    }
    return res;
}