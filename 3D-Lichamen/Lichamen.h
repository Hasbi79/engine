//
// Created by hassa on 26/03/2025.
//

#ifndef LICHAMEN_H
#define LICHAMEN_H

#include "../dataStructures.h"
#include "../gegevenClasses/ini_configuration.h"

#include "../gegevenClasses/l_parser.h"
#include "../gegevenClasses/vector3d.h"

#include "../gegevenClasses/easy_image.h"
#include <string>

using namespace std;
class Lichamen {
public:
    Figures3D generate3DLichamen(const ini::Configuration& configuration);
    Figure createCube();
    Figure createTetrahedron();
    Figure createOctahedron();
    Figure createIcosahedron();
    Figure createDodecahedron();
    Figure createSphere(const int n);
    Figure createCone(const int n, const double h);
    Figure createCylinder(const int n, const double h);
    Figure createTorus(const double r, const double R, const int n, const int m);


};

#endif //LICHAMEN_H
