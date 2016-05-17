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
                    std::shared_ptr<Entity> p( new Road((i*4-100),0,(j*4-100),1,1,1,true, Entity::Type::NOTCOLLIDABLE) );
                    entities.push_back(p);
                    break;
                }
                case 4: {
                    std::shared_ptr<Entity> p( new Barrier((i*4-100),0,(j*4-100),1,1,1,true, Entity::Type::COLLIDABLE, UP) );
                    entities.push_back(p);
                    break;
                }
                case 6: {
                    std::shared_ptr<Entity> p( new Ramp((i*4-100),0,(j*4-100),1,2,5,true, Entity::Type::RAMP));
                    entities.push_back(p);
                    break;
                }
                case 7: {
                    std::shared_ptr<Entity> p( new Tree((i*4-100),0,(j*4-100),1,1,1,true, Entity::Type::COLLIDABLE) );
                    entities.push_back(p);
                    break;
                }
            }
        }
    }
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
                defineTrack(m, leftTrackX, leftTrackZ, start.direction, entities);
            } else {
                printf("LeftTrack missaligned at X:%d Z:%d\n", leftTrackX, leftTrackZ);
            }
            
            if (m[rightTrackX][rightTrackZ] == 5) {
                defineTrack(m, rightTrackX, rightTrackZ, start.direction, entities);
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
                defineTrack(m, leftTrackX, leftTrackZ, start.direction, entities);
            } else {
                printf("LeftTrack missaligned at X:%d Z:%d\n", leftTrackX, leftTrackZ);
            }
            
            if (m[rightTrackX][rightTrackZ] == 5) {
                defineTrack(m, rightTrackX, rightTrackZ, start.direction, entities);
            } else {
                printf("RightTrack missaligned at X:%d Z:%d\n", rightTrackX, rightTrackZ);
            }
            
            break;
        }
    }
}

void addBarrier(int x, int z, int length, Direction direction, std::vector<std::shared_ptr<Entity>> &entities) {
    switch (direction) {
        case UP: {
            for (int i = 0; i < length; i++) {
                //TODO
                //std::shared_ptr<Entity> p(new Barrier(((x-i)*4-100),0,(z*4-100),1,1,1,true, Entity::Type::COLLIDABLE, direction));
                //entities.push_back(p);
            }
            break;
        }
        case DOWN: {
            for (int i = 0; i < length; i++) {
                //TODO
                //std::shared_ptr<Entity> p(new Barrier(((x+i)*4-100),0,(z*4-100),1,1,1,true, Entity::Type::COLLIDABLE, direction));
                //entities.push_back(p);
            }
            break;
        }
        case LEFT: {
            for (int i = 0; i < length; i++) {
                //TODO
                //std::shared_ptr<Entity> p(new Barrier((x*4-100),0,((z-i)*4-100),1,1,1,true, Entity::Type::COLLIDABLE, direction));
                //entities.push_back(p);
            }
            break;
        }
        case RIGHT: {
            for (int i = 0; i < length; i++) {
                //TODO
                //std::shared_ptr<Entity> p(new Barrier((x*4-100),0,((z+i)*4-100),1,1,1,true, Entity::Type::COLLIDABLE, direction));
                //entities.push_back(p);
            }
            break;
        }
    }
}

void defineTrack(map &m, int startX, int startZ, Direction direction, std::vector<std::shared_ptr<Entity>> &entities) {
    switch (direction) {
        case UP: {
            // up
            // vvv
            //  4
            printf("UP\n");
            int length = 1;
            
            int nextXv2 = m[startX-length][startZ];
            
            while (nextXv2 == 4) {
                length++;
                nextXv2 = m[startX-length][startZ];
            }
            
            // make entity with length, direction up
            printf("New barrier at X:%d Z:%d length:%d direction:UP\n", startX, startZ, length);
            addBarrier(startX, startZ, length, direction, entities);
            
            int nextXv1 = m[startX-length][startZ-1];
            int nextXv3 = m[startX-length][startZ+1];
            if (nextXv1 == 4) {
                // go left
                defineTrack(m, startX-length, startZ-1, LEFT, entities);
            } else if (nextXv3 == 4) {
                // go right
                defineTrack(m, startX-length, startZ+1, RIGHT, entities);
            } else {
                printf("Map ambiguous at X:%d Z:%d nextXv1:%d nextXv2:%d nextXv3:%d\n", startX-length, startZ, nextXv1, nextXv2, nextXv3);
            }
            
            break;
        }
        case DOWN: {
            // down
            //  4
            // vvv
            printf("DOWN\n");
            int length = 1;
            
            int nextXv2 = m[startX+length][startZ];
            
            while (nextXv2 == 4) {
                length++;
                nextXv2 = m[startX+length][startZ];
            }
            
            // make entity with length, direction up
            printf("New barrier at X:%d Z:%d length:%d direction:DOWN\n", startX, startZ, length);
            addBarrier(startX, startZ, length, direction, entities);
            
            int nextXv1 = m[startX+length][startZ-1];
            int nextXv3 = m[startX+length][startZ+1];
            if (nextXv1 == 4) {
                // go left
                defineTrack(m, startX+length, startZ-1, LEFT, entities);
            } else if (nextXv3 == 4) {
                // go right
                defineTrack(m, startX+length, startZ+1, RIGHT, entities);
            } else {
                printf("Map ambiguous at X:%d Z:%d nextXv1:%d nextXv2:%d nextXv3:%d\n", startX+length, startZ, nextXv1, nextXv2, nextXv3);
            }
            
            break;
        }
        case RIGHT: {
            // right
            //  v
            // 4v
            //  v
            printf("RIGHT\n");
            int length = 1;
            
            int nextXv2 = m[startX][startZ+length];
            
            while (nextXv2 == 4) {
                length++;
                nextXv2 = m[startX][startZ+length];
            }
            
            // make entity with length, direction up
            printf("New barrier at X:%d Z:%d length:%d direction:RIGHT\n", startX, startZ, length);
            addBarrier(startX, startZ, length, direction, entities);
            
            int nextXv1 = m[startX-1][startZ+length];
            int nextXv3 = m[startX+1][startZ+length];
            if (nextXv1 == 4) {
                // go left
                defineTrack(m, startX-1, startZ+length, UP, entities);
            } else if (nextXv3 == 4) {
                // go right
                defineTrack(m, startX+1, startZ+length, DOWN, entities);
            } else {
                printf("Map ambiguous at X:%d Z:%d nextXv1:%d nextXv2:%d nextXv3:%d\n", startX, startZ+length, nextXv1, nextXv2, nextXv3);
            }
            
            break;
        }
        case LEFT: {
            // left
            // v
            // v4
            // v
            printf("LEFT\n");
            int length = 1;
            
            int nextXv2 = m[startX][startZ-length];
            
            while (nextXv2 == 4) {
                length++;
                nextXv2 = m[startX][startZ-length];
            }
            
            // make entity with length, direction up
            printf("New barrier at X:%d Z:%d length:%d direction:LEFT\n", startX, startZ, length);
            addBarrier(startX, startZ, length, direction, entities);
            
            int nextXv1 = m[startX-1][startZ-length];
            int nextXv3 = m[startX+1][startZ-length];
            if (nextXv1 == 4) {
                // go left
                defineTrack(m, startX-1, startZ-length, UP, entities);
            } else if (nextXv3 == 4) {
                // go right
                defineTrack(m, startX+1, startZ-length, DOWN, entities);
            } else {
                printf("Map ambiguous at X:%d Z:%d nextXv1:%d nextXv2:%d nextXv3:%d\n", startX, startZ-length, nextXv1, nextXv2, nextXv3);
            }
            
            break;
        }
    }
}
