//
// Created by Hassane Balde on 18/03/2025.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include "iostream"
#include "gegevenClasses/vector3d.h"

#include "face.h"
#include "list"



class figure {
private:
    std::vector<Vector3D> points; // Alle punten in de figuur
    std::vector<face> faces;       // Alle vlakken die naar punten verwijzen
public:

    // Constructor
    figure();

    // Methode om een punt toe te voegen
    void addPoint(const Vector3D& point);

    // Methode om een vlak toe te voegen (met indices naar punten)
    void addFace(const std::vector<int>& indices);

    Matrix scalefigure(const double scale);

    Matrix rotateX(const double angle);
    Matrix rotateY(const double angle);
    Matrix rotateZ(const double angle);

    Matrix translatie( const Vector3D & vector);

    void applyTransformation(figure& fig, const Matrix & m);

    static void toPolar(const Vector3D &point, double &theta, double &phi, double &r) ;


    Matrix computeMatrix(const double scale, const double angleX, const double angleY, const double angleZ,
                                 const Vector3D &vector,Matrix& eyePoint);

    Matrix eyePointTrans(const Vector3D& eyePoint);




};


#endif //ENGINE_FIGURE_H
