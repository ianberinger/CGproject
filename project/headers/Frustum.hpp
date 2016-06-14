#ifndef Frustum_h
#define Frustum_h

#include "Renderer.h"

class Frustum {
 private:
  enum { TOP = 0, BOTTOM, LEFT, RIGHT, NEARP, FARP };

 public:
  enum { OUTSIDE, INTERSECT, INSIDE };

  // Plane pl[6];

  vmml::Vector3f ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr, X, Y, Z, camPos;
  float nearD, farD, ratio, angle;
  float sphereFactorX, sphereFactorY;
  double tang;
  double nw, nh, fw, fh;

  // Frustum();
  //~Frustum();

  void setFrustum(float *m);
  void setCamInternals(float angle, float radius, float nearD, float farD);
  void setCamDef(vmml::Vector3f p, vmml::Vector3f l, vmml::Vector3f u);
  bool pointInFrustum(vmml::Vector3f p);
  // int sphereInFrustum(vmml::Vector3f p, float radius);
  // int boxInFrustum(AABox &b);
  /*
    void drawPoints();
    void drawLines();
    void drawPlanes();
    void drawNormals();

    void printPlanes();
   */
};

#endif /* Frustum_h */
