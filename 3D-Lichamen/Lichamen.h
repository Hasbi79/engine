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

    Figures3D read3DLichamen(const ini::Configuration& configuration);
    Figure createCube();
    Figure createTetrahedron();
    Figure createOctahedron();
    Figure createicosahedron();
    Figure createSphere(const int n);
    Figure createCone(const int n, const double h);


};



#endif //LICHAMEN_H
