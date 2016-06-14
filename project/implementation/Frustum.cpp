#include "Frustum.hpp"

#define HALF_ANG2RAD 3.14159265358979323846 / 360.0

void Frustum::setCamInternals(float angle, float ratio, float nearD,
                              float farD) {
  // store the information
  this->ratio = ratio;
  this->angle = angle * HALF_ANG2RAD;
  this->nearD = nearD;
  this->farD = farD;

  // compute width and height of the near and far plane sections
  tang = tan(this->angle);
  sphereFactorY =
      1.0 / cos(this->angle);  // tang * sin(this->angle) + cos(this->angle);

  float anglex = atan(tang * ratio);
  sphereFactorX = 1.0 / cos(anglex);  // tang*ratio * sin(anglex) + cos(anglex);

  nh = nearD * tang;
  nw = nh * ratio;

  fh = farD * tang;
  fw = fh * ratio;
}

void Frustum::setCamDef(vmml::Vector3f p, vmml::Vector3f l, vmml::Vector3f u) {
  vmml::Vector3f dir, nc, fc;

  camPos = p;

  // compute the Z axis of camera
  Z = p - l;
  Z.normalize();

  // X axis of camera of given "up" vector and Z axis
  X = u * Z;
  X.normalize();

  // the real "up" vector is the cross product of Z and X
  Y = Z * X;

  // compute the center of the near and far planes
  nc = p - Z * nearD;
  fc = p - Z * farD;

  // compute the 8 corners of the frustum
  ntl = nc + Y * nh - X * nw;
  ntr = nc + Y * nh + X * nw;
  nbl = nc - Y * nh - X * nw;
  nbr = nc - Y * nh + X * nw;

  ftl = fc + Y * fh - X * fw;
  fbr = fc - Y * fh + X * fw;
  ftr = fc + Y * fh + X * fw;
  fbl = fc - Y * fh - X * fw;

  // compute the six planes
  // the function set3Points asssumes that the points
  // are given in counter clockwise order
  /*
pl[TOP].set3Points(ntr, ntl, ftl);
pl[BOTTOM].set3Points(nbl, nbr, fbr);
pl[LEFT].set3Points(ntl, nbl, fbl);
pl[RIGHT].set3Points(nbr, ntr, fbr);
//	pl[NEARP].set3Points(ntl,ntr,nbr);
//	pl[FARP].set3Points(ftr,ftl,fbl);

pl[NEARP].setNormalAndPoint(-Z, nc);
pl[FARP].setNormalAndPoint(Z, fc);
*/
  vmml::Vector3f aux, normal;

  aux = (nc + Y * nh) - p;
  normal = aux * X;
  // pl[TOP].setNormalAndPoint(normal, nc + Y * nh);

  aux = (nc - Y * nh) - p;
  normal = X * aux;
  // pl[BOTTOM].setNormalAndPoint(normal, nc - Y * nh);

  aux = (nc - X * nw) - p;
  normal = aux * Y;
  // pl[LEFT].setNormalAndPoint(normal, nc - X * nw);

  aux = (nc + X * nw) - p;
  normal = Y * aux;
  // pl[RIGHT].setNormalAndPoint(normal, nc + X * nw);
}

bool Frustum::pointInFrustum(vmml::Vector3f p) {
  float pcz, pcx, pcy, aux;

  // compute vector from camera position to p
  vmml::Vector3f v = p - camPos;

  // compute and test the Z coordinate
  pcz = v.dot(-Z);
  if (pcz > farD || pcz < nearD) return false;

  // compute and test the Y coordinate
  pcy = v.dot(Y);
  aux = pcz * tang;
  if (pcy > aux || pcy < -aux) return false;

  // compute and test the X coordinate
  pcx = v.dot(X);
  aux = aux * ratio;
  if (pcx > aux || pcx < -aux) return false;

  return true;
}
