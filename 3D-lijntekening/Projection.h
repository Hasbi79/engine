#ifndef PROJECTION_H
#define PROJECTION_H

#include "../dataStructures.h"
#include "../gegevenClasses/ini_configuration.h"


#include <fstream>
#include <iostream>


#include <limits>
#include "../gegevenClasses/l_parser.h"

#include "../dataStructures.h"
#include "algorithm"

using namespace std;

// Function to project a single 3D point to 2D
Point2D doProjection(const Vector3D &point,  double d);

// Function to project an entire list of 3D figures into 2D lines
Lines2D doProjection(const Figures3D &figs);


Figures3D generate3DFigures(const ini::Configuration & configuration);

#endif // PROJECTION_H
