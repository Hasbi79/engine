//
// Created by hassa on 26/03/2025.
//

#include "Lichamen.h"
#include <complex>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Figures3D Lichamen::generate3DLichamen(const ini::Configuration &configuration) {

    Figures3D figures;
    vector<double> eyeValues = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::point(eyeValues[0],eyeValues[1],eyeValues[2]);
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    for (int i = 0; i < nrFigures; i++) {
        string figureName = "Figure" + to_string(i);

        std::string type = configuration[figureName]["type"].as_string_or_die();
        if (type == "LineDrawing") {
            // Dit is geen lichaam → skip
            continue;
        }
        Figure figure;
        if (type == "Cube") {
            figure = createCube();
        } else if (type == "Tetrahedron") {
            figure = createTetrahedron();
        } else if (type == "Octahedron") {
            figure = createOctahedron();
        } else if (type == "Icosahedron") {
            figure = createIcosahedron();
        } else if (type == "Dodecahedron") {
            figure = createDodecahedron();
        } else if (type == "Sphere") {
            int n = configuration[figureName]["n"].as_int_or_die();
            figure = createSphere(n);
        } else if (type == "Cone") {
            int n = configuration[figureName]["n"].as_int_or_die();
            double h = configuration[figureName]["height"].as_double_or_die();
            figure = createCone(n, h);
        } else if (type == "Cylinder") {
            int n = configuration[figureName]["n"].as_int_or_die();
            double h = configuration[figureName]["height"].as_double_or_die();
            figure = createCylinder(n, h);
        } else if (type == "Torus") {
            double r = configuration[figureName]["r"].as_double_or_die();
            double R = configuration[figureName]["R"].as_double_or_die();
            int n = configuration[figureName]["n"].as_int_or_die();
            int m = configuration[figureName]["m"].as_int_or_die();
            figure = createTorus(r, R, n, m);
        } else {
            std::cerr << "Onbekend type: " << type << std::endl;
            continue;
        }

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
        {{0,4,2,6}},
        {{4,1,7,2}},
        {{1,5,3,7}},
        {{5,0,6,3}},
        {{6,2,7,3}},
        {{0,5,1,4}}
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
        {{0,1,2}},  // Face 1: P1, P2, P4
        {{1,3,2}},  // Face 2: P1, P3, P2
        {{0,3,1}},  // Face 3: P1, P4, P3
        {{0,2,3}}   // Face 4: P2, P3, P4
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
            {{0, 1, 5}},  // 1 2 6
            {{1, 2, 5}},  // 2 3 6
            {{2, 3, 5}},  // 3 4 6
            {{3, 0, 5}},  // 4 1 6
            {{1, 0, 4}},  // 2 1 5
            {{2, 1, 4}},  // 3 2 5
            {{3, 2, 4}},  // 4 3 5
            {{0, 3, 4}}   // 1 4 5
    };
    return octahedron;
}

Figure Lichamen::createIcosahedron() {

    Figure icosahedron;

    icosahedron.points.push_back(Vector3D::point(0,0,std::sqrt(5) / 2));

    for (int i = 2; i <= 6; i ++) {
        double x = std::cos( (i - 2) * 2 * M_PI / 5);
        double y = std::sin( (i- 2) * 2 * M_PI / 5);
        double z = 0.5;
        icosahedron.points.push_back(Vector3D::point(x,y,z));
    }

    for (int i = 7; i <= 11; i ++) {
        double x = std::cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5);
        double y = std::sin(M_PI / 5 + (i- 7) * 2 * M_PI / 5);
        double z = -0.5;
        icosahedron.points.push_back(Vector3D::point(x,y,z));
    }

    icosahedron.points.push_back(Vector3D::point(0,0,-std::sqrt(5) / 2));
    icosahedron.faces = {
            // 1 face is 1 driehoek je hebt 20 driehoeken
            {{0,1,2}}, {{0,2,3}}, {{0,3,4}}, {{0,4,5}}, {{0,5,1}},
            {{1,6,2}}, {{2,6,7}}, {{2,7,3}}, {{3,7,8}}, {{3,8,4}},
            {{4,8,9}}, {{4,9,5}}, {{5,9,10}}, {{5,10,1}}, {{1,10,6}},
            {{11,7,6}}, {{11,8,7}}, {{11,9,8}}, {{11,10,9}}, {{11,6,10}}
    };

    return icosahedron;
}

Figure Lichamen::createDodecahedron() {

    Figure dodecahedron;
    Figure ico = createIcosahedron();

    for (const auto &f : ico.faces) {
        Vector3D A = ico.points[f.point_indexes[0]];
        Vector3D B = ico.points[f.point_indexes[1]];
        Vector3D C = ico.points[f.point_indexes[2]];

        Vector3D midpoint = Vector3D::point(
                (A.x + B.x + C.x) / 3.0,
                (A.y + B.y + C.y) / 3.0,
                (A.z + B.z + C.z) / 3.0
        );

        dodecahedron.points.push_back(midpoint);
    }
    dodecahedron.faces = {

        {{0, 1, 2, 3, 4}},     // eerste vijfhoek
        {{0, 5, 6, 7, 1}},
        {{1,7,8,9,2}},
        {{2,9,10,11,3}},
        {{3,11,12,13,4}},
        {{4,13,14,5,0}},
        {{19,18,17,16,15}},
        {{19,14,13,12,18}},
        {{18,12,11,10,17}},
        {{17,10,9,8,16}},
        {{16,8,7,6,15}},
        {{15,6,5,14,19}}

    };
    return dodecahedron;
}

Figure Lichamen::createSphere(const int  n) {

    Figure icosahedron = createIcosahedron();

    std::vector<Vector3D> sphPoints = icosahedron.points; // Originele punten van de icosahedron
    std::vector<Face> sphFaces = icosahedron.faces; // Originele faces van de icosahedron

    for (int i = 0; i < n; i ++) {

        std::vector<Face> newFaces;  // Nieuwe verzameling driehoeken
        std::vector<Vector3D> newPoints = icosahedron.points;  // Kopie van de originele punten


         for (auto & f : sphFaces) {
            Vector3D A = sphPoints[f.point_indexes[0]];
            Vector3D B = sphPoints[f.point_indexes[1]];
            Vector3D C = sphPoints[f.point_indexes[2]];

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
    Figure cone;

    // Stap 1: basispunten op de cirkel (z = 0)
    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        double x = std::cos(angle);
        double y = std::sin(angle);
        cone.points.push_back(Vector3D::point(x, y, 0));
    }

    // Stap 2: top van de kegel op (0, 0, h)
    cone.points.push_back(Vector3D::point(0, 0, h));
    int topIndex = cone.points.size() - 1;

    // Stap 3: zijvlakken (driehoeken)
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        Face sideFace;
        sideFace.point_indexes = {i, next, topIndex};
        cone.faces.push_back(sideFace);
    }

    // Stap 4: grondvlak (onderkant cirkel)
    std::vector<int> baseFace;
    for (int i = n - 1; i >= 0; --i) {
        baseFace.push_back(i);
    }
    cone.faces.push_back(baseFace);

    return cone;
}

Figure Lichamen::createCylinder(const int n, const double h) {

    Figure cylinder;

    for (int i = 0; i < n; i++) {
        double angle = 2 * M_PI * i / n;
        double x = std::cos(angle);
        double y = std::sin(angle);
        // 2n punten maken grondvlak en bovenvlak
        cylinder.points.push_back(Vector3D::point(x, y, 0));
        cylinder.points.push_back(Vector3D::point(x, y, h));
    }

    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;

        Face sideFace;
        sideFace.point_indexes = {i * 2, next * 2, next * 2 + 1, i * 2 + 1}; // tegenwijzerzin
        cylinder.faces.push_back(sideFace);
    }

// Grondvlak in omgekeerde volgorde
    std::vector<int> bottomFace;
    for (int i = n - 1; i >= 0; --i) {
        bottomFace.push_back(i * 2);
    }
    cylinder.faces.push_back(bottomFace);

// Bovenvlak in normale volgorde
    std::vector<int> topFace;
    for (int i = 0; i < n; ++i) {
        topFace.push_back(i * 2 + 1);
    }
    cylinder.faces.push_back(topFace);

    return cylinder;

}

Figure Lichamen::createTorus(const double r, const double R, const int n, const int m) {
    Figure torus;

    // Puntgeneratie
    for (int i = 0; i < n; ++i) {
        double u = 2 * M_PI * i / n;
        for (int j = 0; j < m; ++j) {
            double v = 2 * M_PI * j / m;

            double x = (R + r * std::cos(v)) * std::cos(u);
            double y = (R + r * std::cos(v)) * std::sin(u);
            double z = r * std::sin(v);

            torus.points.push_back(Vector3D::point(x, y, z));
        }
    }

    // Zijvlakken (vierhoeken)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int current = i * m + j;
            int right   = ((i + 1) % n) * m + j;
            int diag    = ((i + 1) % n) * m + (j + 1) % m;
            int up      = i * m + (j + 1) % m;

            Face f;
            f.point_indexes = {current, right, diag, up};  // tegenwijzerzin
            torus.faces.push_back(f);
        }
    }

    return torus;
}