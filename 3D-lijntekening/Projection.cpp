//
// Created by hassa on 21/03/2025.
//

#include "Projection.h"


Point2D doProjection(const Vector3D &point, double d) {
    d = 1;
    Point2D ProjectedPoint;
    ProjectedPoint.x = (d*point.x)/-point.z;
    ProjectedPoint.y = (d*point.y)/-point.z;
    return ProjectedPoint;
}
Lines2D doProjection(const Figures3D &figs) {
    Lines2D lines;

    for (const auto &fig : figs) {
        for (const auto &face : fig.faces) {
            if (face.point_indexes.size() < 2) continue;

            Point2D point1 = doProjection(fig.points[face.point_indexes[0]], 1.0);
            Point2D point2 = doProjection(fig.points[face.point_indexes[1]], 1.0);

            Line2D line;
            line.p1 = point1;
            line.p2 = point2;
            line.color = fig.color;

            lines.push_back(line);
        }
    }
    return lines;
}

Figures3D generate3DFigures(const ini::Configuration & configuration) {

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
        int nrPoints = configuration[figureName]["nrPoints"].as_int_or_die();
        for (int pointIndex = 0; pointIndex < nrPoints; pointIndex++) {

            string pointNumber = "point" + to_string(pointIndex);
            vector<double> pointValues = configuration[figureName][pointNumber].as_double_tuple_or_die();
            figure.points.push_back(Vector3D::point(pointValues[0], pointValues[1], pointValues[2]));

        }
        int nrLines = configuration[figureName]["nrLines"].as_int_or_die();
        for (int lineIndex = 0; lineIndex < nrLines; lineIndex++) {
            string lineName = "line" + to_string(lineIndex);
            vector<int> lineValues = configuration[figureName][lineName].as_int_tuple_or_die();

            // Create a Face object for each line
            Face lineFace;
            lineFace.point_indexes.push_back(lineValues[0]); // First point index
            lineFace.point_indexes.push_back(lineValues[1]); // Second point index

            // Add the face to the figure
            figure.faces.push_back(lineFace);

        }

        Matrix eyePointTrans = figure.eyePointTrans(eye);
        Matrix computedMatrix = figure.computeMatrix(scale,rotateX,rotateY,rotateZ,center,eyePointTrans);

        figure.applyTransformation(computedMatrix);

        figures.push_back(figure);

    }

    return figures;

}
