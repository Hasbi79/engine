//
// Created by hassa on 26/03/2025.
//

#ifndef LSYSTEM2D_H
#define LSYSTEM2D_H
#include "../dataStructures.h"
#include "../gegevenClasses/ini_configuration.h"
#include "../gegevenClasses/l_parser.h"
#include "../gegevenClasses/vector3d.h"
#include "cmath"
#include "stack"
#include <iostream>

#include <string>
#include <fstream>
#include "../gegevenClasses/easy_image.h"
#include <limits>
#include "algorithm"




#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



class LSystem2D {

    Line2D generate2DLines(const ini::Configuration &configuration);

    img::EasyImage draw2DLines(const Lines2D & lines,  int size, const Color& backgroundColor);
};



#endif //LSYSTEM2D_H
