#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>

#include <cmath>
#include <string>
#include <vector>

#include "Barrier.hpp"
#include "Entity.hpp"
#include "Ramp.hpp"
#include "Road.hpp"
#include "Tree.hpp"

typedef int map[50][50];

struct marker {
  bool isValid;
  int z;
  int x;
  float angle;
  Direction direction;
};

struct modifier {
  int x;
  int z;
  std::string name;
};

marker loadMap(std::string filePath, map &m,
               std::vector<std::shared_ptr<Entity>> &entities,
               std::vector<marker> &checkpoints);

struct marker identifyMarker(map &m, int i, int j);

void defineTracks(map &m, marker start,
                  std::vector<std::shared_ptr<Entity>> &entities);
void defineTrack(map &m, int startX, int startZ, Direction direction,
                 std::vector<std::shared_ptr<Entity>> &entities,
                 bool generateRoad);
void addRoad(map &m, int x, int z, Direction direction,
             std::vector<std::shared_ptr<Entity>> &entities);
void addBarrier(int x, int z, int length, Direction direction,
                std::vector<std::shared_ptr<Entity>> &entities);
Direction nextDirection(Direction currentDirection, bool firstCase);
bool recurse(map &m, int case1X, int case1Z, int case2X, int case2Z,
             Direction direction,
             std::vector<std::shared_ptr<Entity>> &entities, bool generateRoad);

#endif /* Map_hpp */
