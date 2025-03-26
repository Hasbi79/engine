//
// Created by hassa on 21/03/2025.
//

#ifndef L2D_H
#define L2D_H

#include "vector"
#include "gegevenClasses/vector3d.h"





class Color{
public:
    double red;
    double green;
    double blue;
};

class Point2D{
public:
    double x;
    double y;
};

class Line2D{
public:
    Point2D p1;
    Point2D p2;
    Color color;
};

using Lines2D = std::vector<Line2D>;

class Face
{
public:
    Face() {}

    Face(const std::vector<int> &pointIndexes);

public:

    std::vector<int> point_indexes;
};






class  Figure;
typedef std::vector<Figure> Figures3D;

class Figure
{
public:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color color;

    Matrix scalefigure(const double scale);

    Matrix rotateX(const double angle);
    Matrix rotateY(const double angle);
    Matrix rotateZ(const double angle);

    Matrix translatie_matrix( const Vector3D & vector);

    void applyTransformation(const Matrix &m);

    Matrix computeMatrix(const double scale, const double angleX, const double angleY, const double angleZ,
                                 const Vector3D &vector,Matrix& eyePoint);

    Matrix eyePointTrans(const Vector3D& eyePoint);
    static void eyePointHelpFunctiontoPolar( const Vector3D &point, double &theta, double &phi, double &r);

    static void applyTransformationToFigures(Figures3D &figures, const Matrix &m);


};





#endif //L2D_H
