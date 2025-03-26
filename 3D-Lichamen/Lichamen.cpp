//
// Created by hassa on 26/03/2025.
//

#include "Lichamen.h"
#include <complex>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Figures3D Lichamen::read3DLichamen(const ini::Configuration &configuration) {

    Figures3D figures;
    vector<double> eyeValues = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::point(eyeValues[0],eyeValues[1],eyeValues[2]);
    Figure figure;
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    for (int i = 0; i < nrFigures; i++) {
        string figureName = "Figure" + to_string(i);

        double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
        double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
        double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
        double scale = configuration[figureName]["scale"].as_double_or_die();

        vector<double> centerValues = configuration[figureName]["center"].as_double_tuple_or_die();
        Vector3D center = Vector3D::point(centerValues[0], centerValues[1], centerValues[2]);
        vector<double> colorValues = configuration[figureName]["color"].as_double_tuple_or_die();
        Color lineColor;
        lineColor.red = colorValues[0];
        lineColor.green = colorValues[1];
        lineColor.blue = colorValues[2];

        figure.color = lineColor;

        Matrix eyePointTrans = figure.eyePointTrans(eye);
        Matrix computedMatrix = figure.computeMatrix(scale,rotateX,rotateY,rotateZ,center,eyePointTrans);

        figure.applyTransformation(computedMatrix);

        figures.push_back(figure);

    }



    return figures;
}

Figure Lichamen::createCube() {
    Figure cube;

    cube.points = {
        Vector3D::point(1,-1,-1),
        Vector3D::point(-1,1,-1),
        Vector3D::point(1,1,1),
        Vector3D::point(-1,-1,1),
        Vector3D::point(1,1,-1),
        Vector3D::point(-1,-1,-1),
        Vector3D::point(1,-1,1),
        Vector3D::point(-1,1,1),
    };

    cube.faces = {
        {{0,4,2,6,0}},
        {{4,1,7,2,4}},
        {{1,5,3,7,1}},
        {{5,0,6,3,5}},
        {{6,2,7,3,6}},
        {{0,5,1,4,0}}
    };

    return cube;
}

Figure Lichamen::createTetrahedron() {

    Figure tetrahedron;

    tetrahedron.points = {
        Vector3D::point(1,-1,-1),
        Vector3D::point(-1,1,-1),
        Vector3D::point(1,1,1),
        Vector3D::point(-1,-1,1)
    };

    tetrahedron.faces = {
        {{0,1,2,0}},  // Face 1: P1, P2, P4
        {{1,3,2,1}},  // Face 2: P1, P3, P2
        {{0,3,1,0}},  // Face 3: P1, P4, P3
        {{0,2,3,0}}   // Face 4: P2, P3, P4
    };

    return tetrahedron;

}

Figure Lichamen::createOctahedron() {
    Figure octahedron;

    octahedron.points = {
        Vector3D::point(1, 0, 0),
        Vector3D::point(0, 1, 0),
        Vector3D::point(-1, 0, 0),
        Vector3D::point(0, -1, 0),
        Vector3D::point(0, 0, -1),
        Vector3D::point(0, 0, 1)
    };

    octahedron.faces = {
        {{0,1,5,0}},
        {{0,1,5,0}},
        {{2,3,5,2}},
        {{3,0,5,3}},
        {{1,0,4,1}},
        {{2,1,4,2}},
        {{3,2,4,3}},
        {{0,3,4,0}}
    };
    return octahedron;
}

Figure Lichamen::createicosahedron() {

    Figure icosahedron;

    icosahedron.points.push_back(Vector3D::point(0,0,std::sqrt(5) / 2));

    for (int i = 2; i <= 6; i ++) {
        double x = std::cos( (i - 2) * 2 * M_PI / 5);
        double y = std::sin( (i-2) * 2* M_PI/5);
        double z = 0.5;
        icosahedron.points.push_back(Vector3D::point(x,y,z));
    }

    for (int i = 7; i <= 11; i ++) {
        double x = std::cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5);
        double y = std::sin(M_PI/5 + (i-7) * 2* M_PI/5);
        double z = -0.5;
        icosahedron.points.push_back(Vector3D::point(x,y,z));
    }

    icosahedron.points.push_back(Vector3D::point(0,0,-std::sqrt(5) / 2));

    icosahedron.faces = {
        {{0,1,2,0}},
        {{0,2,3,0}},
        {{0,3,4,0}},
        {{0,4,5,0}},
        {{0,5,1,0}},
        {{1,6,2,1}},
        {{1,6,2,1}},
        {{2,6,7,2}},
        {{2,7,3,2}},
        {{3,7,8,3}},
        {{3,8,4,3}},
        {{4,8,9,4}},
        {{4,9,5,4}},
        {{5,9,10,5}},
        {{5,10,1,5}},
        {{1,10,6,1}},
        {{11,7,6,11}},
        {{11,8,7,11}},
        {{11,9,8,11}},
        {{11,10,9,11}},
        {{11,6,10,11}},

    };
    return icosahedron;
}

Figure Lichamen::createSphere(const int  n) {

    Figure icosahedron = createicosahedron();

    std::vector<Vector3D> sphPoints = icosahedron.points; // Originele punten van de icosahedron
    std::vector<Face> sphFaces = icosahedron.faces; // Originele faces van de icosahedron

    for (int i = 0; i < n; i ++) {

        std::vector<Face> newFaces;  // Nieuwe verzameling driehoeken
        std::vector<Vector3D> newPoints = icosahedron.points;  // Kopie van de originele punten

        for (auto & f : icosahedron) {
            Vector3D A = icosahedron.points[0];
            Vector3D B = icosahedron.points[1];
            Vector3D C = icosahedron.points[2];

            Vector3D D;
            Vector3D E;
            Vector3D F;

            D.x = (A.x + B.x) / 2;
            D.y = (A.y + B.y) / 2;
            D.z = (A.z + B.z) / 2;

            E.x = (A.x + C.x) / 2;
            E.y = (A.y + C.y) / 2;
            E.z = (A.z + C.z) / 2;

            F.x = (B.x + C.x) / 2;
            F.y = (B.y + C.y) / 2;
            F.z = (B.z + C.z) / 2;

            // herschalen lengte van elk punt naar 1 van de oorsprong
            A.normalise();
            B.normalise();
            C.normalise();
            D.normalise();
            E.normalise();
            F.normalise();

            newPoints.push_back(A);
            int indexA = newPoints.size() - 1;  // Index van A is de grootte - 1
            newPoints.push_back(B);
            int indexB = newPoints.size() - 1;  // Index van B is de grootte - 1
            newPoints.push_back(C);
            int indexC = newPoints.size() - 1;
            newPoints.push_back(D);
            int indexD = newPoints.size() - 1;
            newPoints.push_back(E);
            int indexE = newPoints.size() - 1;
            newPoints.push_back(F);
            int indexF = newPoints.size() - 1;


            Face f1 = {{indexA, indexD, indexE}};
            Face f2 = {{indexB, indexF, indexD}};
            Face f3 = {{indexC, indexE, indexF}};
            Face f4 = {{indexD, indexF, indexE}};


            newFaces.push_back(f1);
            newFaces.push_back(f2);
            newFaces.push_back(f3);
            newFaces.push_back(f4);
        }

        // Vervang de oude faces en punten door de nieuwe waarden
        sphFaces = newFaces;
        sphPoints = newPoints;
    }
    // Maak een nieuwe Figure met de geüpdatete points en faces en retourneer deze
    Figure sphere;
    sphere.points = sphPoints;
    sphere.faces = sphFaces;
    return sphere;

}

Figure Lichamen::createCone(const int n, const double h) {


}

