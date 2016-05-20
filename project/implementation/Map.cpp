#include "Map.hpp"

marker loadMap(std::string filePath, map &m, std::vector<std::shared_ptr<Entity>> &entities, std::vector<marker> &checkpoints){
    marker start;
    start.isValid = false;
    
    std::string currLine;
    std::ifstream file (filePath);
    int count=0;
    if (file.is_open())
    {
        while ( getline (file,currLine) )
        {
            for(int i=0;i<currLine.length();i++){
                m[count][i]=currLine[i]-'0';
            }
            count++;
        }
        file.close();
    }else{
        
    }
    
    for(int i=0; i<50;i++){
        for(int j=0;j<50;j++){
            switch (m[i][j]) {
                case 1: {
                    if (!start.isValid) {start = identifyMarker(m, i, j);}
                    break;
                }
                case 2: {
                    marker checkpoint = identifyMarker(m, i, j);
                    if (checkpoint.isValid) {
                        bool isCollected = false;
                        for(auto c: checkpoints) {
                            if (c.x == checkpoint.x && c.z == checkpoint.z){
                                // don't use this checkpoint
                                isCollected = true;
                                break;
                            }
                        }
                        if (!isCollected) {checkpoints.push_back(checkpoint);}
                    }
                    break;
                }
                case 3: {
                    std::shared_ptr<Entity> p( new Road(i,0,j,1,1,1,0.0,0.0,true, Entity::Type::NOTCOLLIDABLE) );
                    entities.push_back(p);
                    break;
                }
                case 4: {
                    //std::shared_ptr<Entity> p( new Barrier(i,0,j,1,1,1,10.0,0.0,true, Entity::Type::COLLIDABLE, UP) );
                    //entities.push_back(p);
                    break;
                }
                case 7: {
                    std::shared_ptr<Entity> p( new Tree(i,0,j,1,1,1,10.0,0.0,true, Entity::Type::COLLIDABLE) );
                    entities.push_back(p);
                    break;
                }
            }
        }
    }
    
    defineTracks(m, start, entities);
    return start;
}

marker identifyMarker(map &m, int i, int j) {
    int value = m[i][j];
    
    int right = m[i][j+1];
    int rightright = m[i][j+2];
    int up = m[i+1][j];
    int upup = m[i+2][j];
    
    marker res;
    res.isValid = false;
    
    if (right == value && rightright == value) {
        if (m[i+1][j+1] == value) {
            // 111
            // x1x
            res.isValid = true;
            res.direction = DOWN;
            res.x = i;
            res.z = j+1;
            res.angle = 3*M_PI/2;
        } else if (m[i-1][j+1] == value) {
            // x1x
            // 111
            res.isValid = true;
            res.direction = UP;
            res.x = i;
            res.z = j+1;
            res.angle = M_PI/2;
        }
    } else if (up == value && upup == value) {
        if (m[i+1][j+1] == value) {
            // 1x
            // 11
            // 1x
            res.isValid = true;
            res.direction = RIGHT;
            res.x = i + 1;
            res.z = j;
            res.angle = M_PI;
        } else if (m[i+1][j-1] == value){
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

void defineTracks(map &m, marker start, std::vector<std::shared_ptr<Entity>> &entities) {
    switch (start.direction) {
        case UP:
        case DOWN: {
            int leftTrackX = start.x;
            int leftTrackZ = start.z - 2;
            
            int rightTrackX = start.x;
            int rightTrackZ = start.z + 2;
            
            if (m[leftTrackX][leftTrackZ] == 5) {
                defineTrack(m, leftTrackX, leftTrackZ, start.direction, entities, true);
            } else {
                printf("LeftTrack missaligned at X:%d Z:%d\n", leftTrackX, leftTrackZ);
            }
            
            if (m[rightTrackX][rightTrackZ] == 5) {
                defineTrack(m, rightTrackX, rightTrackZ, start.direction, entities, false);
            } else {
                printf("RightTrack missaligned at X:%d Z:%d\n", rightTrackX, rightTrackZ);
            }
            
            break;
        }
        case LEFT:
        case RIGHT: {
            int leftTrackX = start.x - 2;
            int leftTrackZ = start.z;
            
            int rightTrackX = start.x + 2;
            int rightTrackZ = start.z;
            
            if (m[leftTrackX][leftTrackZ] == 5) {
                defineTrack(m, leftTrackX, leftTrackZ, start.direction, entities, true);
            } else {
                printf("LeftTrack missaligned at X:%d Z:%d\n", leftTrackX, leftTrackZ);
            }
            
            if (m[rightTrackX][rightTrackZ] == 5) {
                defineTrack(m, rightTrackX, rightTrackZ, start.direction, entities, false);
            } else {
                printf("RightTrack missaligned at X:%d Z:%d\n", rightTrackX, rightTrackZ);
            }
            
            break;
        }
    }
}

//modifier upMod = {-1, 0};
//modifier downMod = {1, 0};
//modifier leftMod = {0, -1};
//modifier rightMod = {0, 1};


//mods[UP] = {-1, 0};
//mods[DOWN] = {1, 0};
//mods[LEFT] = {0, -1};
//mods[RIGHT] = {0, 1};

Direction nextDirection(Direction currentDirection, bool firstCase) {
    if (firstCase) {
        if (currentDirection == UP || currentDirection == DOWN) {return LEFT;}
        return UP;
    } else {
        if (currentDirection == UP || currentDirection == DOWN) {return RIGHT;}
        return DOWN;
    }
}

bool recurse(map &m, int case1X, int case1Z, int case2X, int case2Z, Direction direction, std::vector<std::shared_ptr<Entity>> &entities, bool generateRoad)
{
    if (m[case1X][case1Z] == 4) {
        defineTrack(m, case1X, case1Z, nextDirection(direction, true), entities, generateRoad);
        return true;
    } else if (m[case2X][case2Z] == 4) {
        // go right
        defineTrack(m, case2X, case2Z, nextDirection(direction, false), entities, generateRoad);
        return true;
    }
    
    return false;
}

modifier mods[5] = {{-1, 0, "UP"}, {0, -1, "LEFT"}, {0, 1, "RIGHT"}, {0, 0, "FILLER"}, {1, 0, "DOWN"}};

void defineTrack(map &m, int startX, int startZ, Direction direction, std::vector<std::shared_ptr<Entity>> &entities,bool generateRoad) {
    int length = 1;
    int xMod = mods[direction].x;
    int zMod = mods[direction].z;
    
    int x = startX+(xMod*length);
    int z = startZ+(zMod*length);
    
    for (int nextXv2 = m[x][z]; nextXv2 == 4; nextXv2 = m[x][z]) {
        length++;
        x = startX+(xMod*length);
        z = startZ+(zMod*length);
    }
    
    // make entity with length, direction up
    printf("New barrier at X:%d Z:%d length:%d direction:%s\n", startX, startZ, length, mods[direction].name.c_str());
    addBarrier(startX, startZ, length, direction, entities);
    if (generateRoad){addRoad(m, startX, startZ, direction, entities);}
    
    // previous row
    int case1X = x-xMod-abs(zMod);
    int case1Z = z-zMod-abs(xMod);
    
    int case2X = x-xMod+abs(zMod);
    int case2Z = z-zMod+abs(xMod);
    
    if(recurse(m, case1X, case1Z, case2X, case2Z, direction, entities, generateRoad)){return;}
    
    // current row
    case1X = x-abs(zMod);
    case1Z = z-abs(xMod);
    
    case2X = x+abs(zMod);
    case2Z = z+abs(xMod);
    
    if(!recurse(m, case1X, case1Z, case2X, case2Z, direction, entities, generateRoad)){
        printf("Map ambiguous at X:%d Z:%d case1X:%d case1Z:%d case2X:%d case2Z:%d\n", x, z, case1X, case1Z, case2X, case2Z);
    }
}

Direction generalDirection = UP;
void addRoad(map &m, int x, int z, Direction direction, std::vector<std::shared_ptr<Entity>> &entities){
    if (direction != generalDirection && (direction == UP || direction == DOWN)){generalDirection = direction;}
    
    
    int length = 0;
    if (generalDirection == UP){
        int endZ = z + 1;
        for (;m[x][endZ] != 4;endZ++) {
            length++;
        }
    } else {
        int endZ = z - 1;
        for (;m[x][endZ] != 4;endZ--) {
            length++;
        }
        z -= length;
    }
    
    if(length > 0) {
        std::shared_ptr<Entity> p( new Road(x,0,z,length,1,1,0.0,0.0,true, Entity::Type::NOTCOLLIDABLE) );
        //std::shared_ptr<Entity> p(new Road(x,0,z,length,1,1,true, Entity::Type::NOTCOLLIDABLE));
        entities.push_back(p);
        //else{std::shared_ptr<Entity> p(new Road(x,0,z-length,length,1,1,true, Entity::Type::NOTCOLLIDABLE));}
        //entities.push_back(std::shared_ptr<Entity>(new Road(x,0,z-length,length,1,1,true, Entity::Type::NOTCOLLIDABLE)));
    }
}

void addBarrier(int x, int z, int length, Direction direction, std::vector<std::shared_ptr<Entity>> &entities) {
    //TODO curves
    switch (direction) {
        case UP: {
            if (length != 1){x = x-(length*0.5);}
            std::shared_ptr<Entity> p(new Barrier(x,0,z,2*length,1,1,10.0,0.0,true, Entity::Type::COLLIDABLE, direction));
            entities.push_back(p);
            break;
        }
        case DOWN: {
            if (length != 1){x = x+(length*0.5);}
            std::shared_ptr<Entity> p(new Barrier(x,0,z,2*length,1,1,10.0,0.0,true, Entity::Type::COLLIDABLE, direction));
            entities.push_back(p);
            break;
        }
        case LEFT: {
            if (length != 1) {z = z-(length*0.5);}
            std::shared_ptr<Entity> p(new Barrier(x,0,z,2*length,1,1,10.0,0.0,true, Entity::Type::COLLIDABLE, direction));
            entities.push_back(p);
            break;
        }
        case RIGHT: {
            if (length != 1) {z = z+(length*0.5);}
            std::shared_ptr<Entity> p(new Barrier(x,0,z,1,1,2*length,10.0,0.0,true, Entity::Type::COLLIDABLE, direction));
            entities.push_back(p);
            break;
        }
    }
}