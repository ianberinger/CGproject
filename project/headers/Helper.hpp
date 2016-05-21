#ifndef Helper_h
#define Helper_h

#include <algorithm>
#include <cstdlib>

class Helper {
 public:
  float randomNumber(float min, float max);
  float clip(float v, float lower, float upper);
};

#endif /* Helper_h */
