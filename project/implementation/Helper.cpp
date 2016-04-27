#include "Helper.h"

/* Helper functions */
float Helper::randomNumber(float min, float max){
    return min + (rand()) / (RAND_MAX / (max - min));
}

float Helper::clip(float v, float lower, float upper){
    return std::max(lower, std::min(v, upper));
}