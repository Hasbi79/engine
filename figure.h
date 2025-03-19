//
// Created by Hassane Balde on 18/03/2025.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "iostream"
#include "vector3d.h"
#include "face.h"

class figure {
public:

    std::vector<Vector3D> points; // Alle punten in de figuur
    std::vector<face> faces;       // Alle vlakken die naar punten verwijzen

    // Constructor
    figure();

    // Methode om een punt toe te voegen
    void addPoint(const Vector3D& point);

    // Methode om een vlak toe te voegen (met indices naar punten)
    void addFace(const std::vector<int>& indices);


};


#endif //ENGINE_FIGURE_H
