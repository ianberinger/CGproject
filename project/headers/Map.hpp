#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>

#include <cmath>
#include <string>
#include <vector>

#include "Tree.hpp"
#include "Barrier.hpp"
#include "Ramp.hpp"
#include "Road.hpp"
#include "Entity.hpp"

typedef int map[50][50];

struct marker {
    bool isValid;
    int z;
    int x;
    float angle;
    Direction direction;
};

marker loadMap(std::string filePath, map &m, std::vector<std::shared_ptr<Entity>> &entities, std::vector<marker> &checkpoints);

struct marker identifyMarker(map &m, int i,int j);

void defineTracks(map &m, marker start, std::vector<std::shared_ptr<Entity>> &entities);
void defineTrack(map &m, int startX, int startZ, Direction direction, std::vector<std::shared_ptr<Entity>> &entities);

#endif /* Map_hpp */
