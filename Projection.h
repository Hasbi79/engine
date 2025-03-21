#ifndef PROJECTION_H
#define PROJECTION_H

#include "dataStructures.h"


// Function to project a single 3D point to 2D
Point2D doProjection(const Vector3D &point,  double d);

// Function to project an entire list of 3D figures into 2D lines
Lines2D doProjection(const Figures3D &figs);

#endif // PROJECTION_H
