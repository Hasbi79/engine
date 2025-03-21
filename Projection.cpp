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

