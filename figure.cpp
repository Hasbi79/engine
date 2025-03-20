//
// Created by Hassane Balde on 18/03/2025.
//

#include "figure.h"
#include "cmath"

// Constructor: Maak een lege figuur
figure::figure() = default;

// Methode om een punt toe te voegen
void figure::addPoint(const Vector3D& point) {
    points.push_back(point);
}


// Methode om een vlak toe te voegen
void figure::addFace(const std::vector<int>& indices) {
    faces.emplace_back(indices);
}

Matrix figure::scalefigure(const double scale) {
    Matrix scaleMatrix;

    scaleMatrix(1,1) = scale;
    scaleMatrix(2,2) = scale;
    scaleMatrix(3,3) = scale;
    scaleMatrix(4,4) = 1;

    return  scaleMatrix;
}

Matrix figure::rotateX(const double angle) {
    Matrix rotateMatrixX;
    double cosinusAngle = cos(angle);
    double sinusAngle = sin(angle);
    double minusSinusAngle = -sin(angle);

    rotateMatrixX(1,1) = 1;
    rotateMatrixX(2,2) = cosinusAngle;
    rotateMatrixX(3,3) = cosinusAngle;
    rotateMatrixX(2,3) = minusSinusAngle;
    rotateMatrixX(3,2) = sinusAngle;
    rotateMatrixX(4,4) = 1;

    return rotateMatrixX;
}

Matrix figure::rotateY(const double angle) {
    Matrix rotateMatrixy;

    double cosinusAngle = cos(angle);
    double sinusAngle = sin(angle);
    double minusSinusAngle = -sin(angle);

    rotateMatrixy(1,1) = cosinusAngle;
    rotateMatrixy(1,3) = minusSinusAngle;
    rotateMatrixy(2,2) = 1;
    rotateMatrixy(3,1) = sinusAngle;
    rotateMatrixy(3,3) = cosinusAngle;

    return rotateMatrixy;
}

Matrix figure::rotateZ(const double angle) {
    Matrix rotateMatrixZ;

    double cosinusAngle = cos(angle);
    double sinusAngle = sin(angle);
    double minusSinusAngle = -sin(angle);

    rotateMatrixZ(1,1) = cosinusAngle;
    rotateMatrixZ(1,2) = sinusAngle;
    rotateMatrixZ(2,1) = minusSinusAngle;
    rotateMatrixZ(2,2) = cosinusAngle;
    rotateMatrixZ(3,3) = 1;
    rotateMatrixZ(4,4) = 1;

    return rotateMatrixZ;
}

Matrix figure::translatie(const Vector3D &vector) {
    Matrix translatieMatrix;

    translatieMatrix(1,1) = 1;
    translatieMatrix(2,2) = 1;
    translatieMatrix(3,3) = 1;
    translatieMatrix(4,4) = 1;
    translatieMatrix(4,1) = vector.x;
    translatieMatrix(4,2) = vector.y;
    translatieMatrix(4,3) = vector.z;

    return translatieMatrix;
}

Matrix figure::computeMatrix(const double scale, const double angleX, const double angleY, const double angleZ,
                             const Vector3D &vector,Matrix& eyePoint) {
    return scalefigure(scale) * rotateX(angleX) * rotateY(angleY) * rotateZ(angleZ) * translatie(vector) * eyePoint;

}


void figure::applyTransformation(figure &fig, const Matrix &m) {

    for(auto & p: fig.points){
        p = p * m;
    }

}


Matrix figure::eyePointTrans(const Vector3D &eyePoint) {

    double theta, phi, r;
    toPolar(eyePoint, theta, phi, r);

    // Maak een identiteitsmatrix
    Matrix V;
    double cosTheta = std::cos(theta);
    double sinTheta = std::sin(theta);
    double cosPhi = std::cos(phi);
    double sinPhi = std::sin(phi);

    V(1,1) = -sinTheta;
    V(1,2) = -cosTheta * cosPhi;
    V(1,3) = cosTheta * sinPhi;

    V(2,1) = cosTheta;
    V(2,2) = -sinTheta * cosPhi;
    V(2,3) = sinTheta * sinPhi;

    V(3,2) = sinPhi;
    V(3,3) = cosPhi;

    V(4,3) = -r;
    V(4,4) = 1;

    return V;

}



void figure::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    // Stap 1: Bereken r
    r = std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);

    // Stap 2: Bereken θ met atan2 (zorgt ervoor dat de hoek correct wordt berekend)
    theta = std::atan2(point.y, point.x);

    // Stap 3: Bereken φ met acos
    phi = std::acos(point.z / r);

}





